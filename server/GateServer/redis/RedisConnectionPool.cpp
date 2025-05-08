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
			continue;
		}

		RedisReply reply{ (redisReply*)redisCommand(context, "AUTH %s", pwd.c_str()) };
		if (reply->type == REDIS_REPLY_ERROR) {
			// 打印日志
			// std::cout << "认证失败" << std::endl;
			continue;
		}

		// 打印日志
		// std::cout << "认证成功" << std::endl;
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

void RedisConnectionPool::close()
{
	if (!_stop) {
		_stop = true;
		_cond.notify_all();
	}
}

RedisConnectionPool::~RedisConnectionPool()
{
	if (!_stop) {
		close();
	}

	std::lock_guard<std::mutex> gurad(_mtx);
	while (!_connections.empty()) {
		_connections.pop();
	}
}
