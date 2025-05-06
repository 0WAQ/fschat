#ifndef _REDISMANAGER_H_
#define _REDISMANAGER_H_

#include <hiredis/hiredis.h>
#include "ulti.h"

/**
 * @brief redis 管理类
 */
class RedisManager : public Singleton<RedisManager>
{
public:
	
	/**
	 * @brief 自定义删除器
	 */
	class deletor
	{
	public:
		void operator() (redisReply* reply) {
			freeReplyObject(reply);
		}
	};

	friend class Singleton<RedisManager>;
	using Reply = std::unique_ptr<redisReply, deletor>;

private:
	RedisManager();
	
public:

	bool connect(const std::string& host, int port);
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
	redisContext* _connect;
};

#endif // _REDISMANAGER_H_