#ifndef _REDISMANAGER_H_
#define _REDISMANAGER_H_

#include <hiredis/hiredis.h>

#include <memory>

#include "ulti.h"
#include "singleton.h"
#include "RedisConnectionPool.h"

/**
 * @brief redis π‹¿Ì¿‡
 */
class RedisManager : public Singleton<RedisManager>
{
public:
	friend class Singleton<RedisManager>;

private:
	RedisManager();
	
public:
	bool get(const std::string& key, std::string& value);
	bool set(const std::string& key, const std::string& value);
	bool auth(const std::string& passwd);
	bool lpush(const std::string& key, const std::string& value);
	bool lpop(const std::string& key, std::string& value);
	bool rpush(const std::string& key, const std::string& value);
	bool rpop(const std::string& key, std::string& value);
	bool hset(const std::string& key, const std::string& hkey, const std::string& value);
	bool hset(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);
	std::string hget(const std::string& key, const std::string& hkey);
	bool del(const std::string& key);
	bool contains(const std::string& key);
	void close();

private:
	std::unique_ptr<RedisConnectionPool> _pool;
};

#endif // _REDISMANAGER_H_