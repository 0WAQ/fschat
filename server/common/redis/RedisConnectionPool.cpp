#include "RedisConnectionPool.h"

RedisConnectionPool::RedisConnectionPool(size_t pool_size, const std::string& host, int port, const std::string& pwd)
	: _pool_size(pool_size)
	, _host(host.c_str())
	, _port(port)
	, _stop(false)
{
	for (size_t i = 0; i < _pool_size; ++i) {
		redisContext* context = redisConnect(_host, port);
		if (!context || context->err) {
			if (context) {
				redisFree(context);
			}
			continue;
		}

		RedisReply reply{ (redisReply*)redisCommand(context, "AUTH %s", pwd.c_str()) };
		if (reply->type == REDIS_REPLY_ERROR) {
			warn("authentication failed.");
			continue;
		}

		debug("authentication success.");
		_connections.push(context);
	}
}

redisContext* RedisConnectionPool::get()
{
	std::unique_lock<std::mutex> lock{ _mtx };
	_cond.wait(lock, [this]() {
			if (_stop) {
				return true;
			}
			return !_connections.empty();
		});

	if (_stop) {
		return {};
	}

	redisContext* context = _connections.front();
	_connections.pop();
	return context;
}

void RedisConnectionPool::ret(redisContext* conn)
{
	std::lock_guard<std::mutex> lock{ _mtx };
	if (_stop) {
		return;
	}

	_connections.push(conn);
	_cond.notify_one();
}

void RedisConnectionPool::clear()
{
	std::lock_guard<std::mutex> gurad(_mtx);
	while (!_connections.empty()) {
		redisFree(_connections.front());
		_connections.pop();
	}
}

void RedisConnectionPool::close()
{
	if (!_stop) {
		_stop = true;
		_cond.notify_all();
		this->clear();
	}
}

RedisConnectionPool::~RedisConnectionPool()
{
	if (!_stop) {
		close();
	}
}
