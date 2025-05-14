#include "SqlConnectionPool.h"

#include <thread>
#include <chrono>
using namespace std::chrono_literals;

SqlConnectionPool::SqlConnectionPool(const std::string& url,
    const std::string& user,
    const std::string& passwd,
    const std::string& schema,
    size_t pool_size)
    : _url(url), _user(user), _passwd(passwd), _schema(schema), _pool_size(pool_size)
{
    try {
        for (size_t i = 0; i < _pool_size; ++i) {
            sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
            sql::Connection* conn = driver->connect(_url, _user, _passwd);
            conn->setSchema(_schema);

            auto current_timestamp = std::chrono::system_clock::now().time_since_epoch();
            long long seconds = current_timestamp.count();
            _pool.push(std::make_unique<SqlConnection>(conn, seconds));
        }

        _check_thread = std::thread([this]() {
                while (!_b_stop) {
                    checkConnection();
                    std::this_thread::sleep_for(60s);
                }
            });
        _check_thread.detach();
    }
    catch (sql::SQLException& e) {
        error("MySQL pool init failed, error is {}.", e.what());
    }
}

std::unique_ptr<SqlConnection> SqlConnectionPool::get()
{
    std::unique_lock<std::mutex> lock{ _mutex };
    _cond.wait(lock, [this]() {
            if (_b_stop) {
                return true;
            }
            return !_pool.empty();
        });
    if (_b_stop) {
        return nullptr;
    }

    std::unique_ptr<SqlConnection> conn{ std::move(_pool.front()) };
    _pool.pop();
    return conn;
}

void SqlConnectionPool::ret(std::unique_ptr<SqlConnection> conn)
{
    if (_b_stop) {
        return;
    }

    std::unique_lock<std::mutex> lock{ _mutex };
    _pool.push(std::move(conn));
    _cond.notify_one();
}

void SqlConnectionPool::checkConnection()
{
    std::lock_guard<std::mutex> guard{ _mutex };

    auto current_timestamp = std::chrono::system_clock::now().time_since_epoch();
    long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(current_timestamp).count();
    
    size_t pool_size = _pool_size;
    for (size_t i = 0; i < pool_size; ++i) {
        auto conn = std::move(_pool.front());
        _pool.pop();

        Defer defer([this, &conn]() {
                _pool.push(std::move(conn));
            });

        if (timestamp - conn->last_access_time() < 5) {
            continue;
        }

        try {
            // TODO: 优化
            std::unique_ptr<sql::Statement> stmt{ conn->conn()->createStatement() };
            stmt->executeQuery("SELECT 1");
            conn->set_last_access_time(timestamp);
            info("execute timer alive query.");
        }
        catch (sql::SQLException& e) {
            error("Error keeping connection alive: {}", e.what());

            sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
            auto newConn = driver->connect(_url, _user, _passwd);
            newConn->setSchema(_schema);
            conn.reset(new SqlConnection{ newConn, timestamp });
        }
    }
}

void SqlConnectionPool::close()
{
    if (_b_stop) {
        return;
    }

    _b_stop = true;
    _cond.notify_all();
}

SqlConnectionPool::~SqlConnectionPool()
{
    if (!_b_stop) {
        close();
    }

    std::unique_lock<std::mutex> lock{ _mutex };
    while (!_pool.empty()) {
        _pool.pop();
    }

    // TODO: 关闭数据库
}
