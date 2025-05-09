#ifndef _REDISCONNECTIONPOOL_H_
#define _REDISCONNECTIONPOOL_H_

#include <hiredis/hiredis.h>

#include <atomic>
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

#include "base/ulti.h"

/**
 * @brief redis Á¬½Ó³Ø
 */
class RedisConnectionPool
{
public:

	RedisConnectionPool(size_t pool_size, const std::string& host, int port, const std::string& pwd);

	redisContext* get();

	void ret(redisContext* conn);

	void clear();

	void close();

	~RedisConnectionPool();

private:
	std::atomic<bool> _stop;
	size_t _pool_size;
	const char* _host;
	int _port;
	std::queue<redisContext*> _connections;
	std::mutex _mtx;
	std::condition_variable _cond;
};

class RedisContext
{
public:
	explicit RedisContext(std::unique_ptr<RedisConnectionPool>& pool)
		: _pool(pool)
		, _context(_pool->get())
	{ }

	operator bool() {
		return _context != nullptr;
	}

	operator redisContext* () {
		return _context;
	}

	~RedisContext() {
		_pool->ret(_context);
	}

private:
	std::unique_ptr<RedisConnectionPool>& _pool;
	redisContext* _context;
};

/**
 * @brief redis ÏìÓ¦
 */
class RedisReply
{
public:

	RedisReply(redisReply* reply) : _reply(reply) {}

	const redisReply* operator->() {
		return _reply;
	}

	bool operator== (const RedisReply& r) {
		return _reply == r._reply;
	}

	~RedisReply() {
		if (_reply) {
			freeReplyObject(_reply);
		}
	}

private:
	redisReply* _reply;
};

#endif // _REDISCONNECTIONPOOL_H_