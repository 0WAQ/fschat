#include "RedisManager.h"
#include "base/ConfigManager.h"

// TODO: ´ıÀ©Õ¹Îª³Ø
RedisManager::RedisManager()
{
	auto& config = ConfigManager::GetInstance();
	auto host = config["Redis"]["Host"];
	auto port = config["Redis"]["Port"];
	auto pwd = config["Redis"]["Passwd"];
	// TODO: pool_size ¶ÁÅäÖÃÎÄ¼ş
	_pool.reset(new RedisConnectionPool(5, host, std::atoi(port.c_str()), pwd));
}

bool RedisManager::get(const std::string& key, std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed! Redis Connection Pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "GET %s", key.c_str())  };
	if (reply == nullptr) {
		error("Execute command [ Get {} ] failed! Empty or nil reply.", key);
		return false;
	}

	if (reply->type != REDIS_REPLY_STRING) {
		error("Execute command [ Get {} ] failed! Invalid reply.", key);
		return false;
	}

	value = reply->str;

	debug("Success to execute command [ Get {} ].", key);
	return true;
}

bool RedisManager::set(const std::string& key, const std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "SET %s %s", key.c_str(), value.c_str()) };

	if (reply == nullptr) {
		error("Execute command [ SET {}:{} failed! Empty or nil reply.", key, value);
		return false;
	}

	if (!(reply->type == REDIS_REPLY_STATUS)
		&& (strcmp(reply->str, "OK") == 0
			|| strcmp(reply->str, "ok")))
	{
		error("Execute command [ SET {}:{} failed! Invalid reply.", key, value);
		return false;
	}

	debug("Success to execute command [ SET {}:{} ].", key, value);
	return true;
}

bool RedisManager::auth(const std::string& passwd)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "AUTH %s", passwd.c_str()) };
	if (reply->type == REDIS_REPLY_ERROR) {
		error("Authentication failed. Invalid reply.");
		return false;
	}

	debug("Authentication success.");
	return true;
}

bool RedisManager::lpush(const std::string& key, const std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "LPUSH %s %s", key.c_str(), value.c_str()) };
	if (reply == nullptr) {
		error("Execute command [ LPUSH {}:{} ] failed. Empty or nil reply.", key, value);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
		error("Execute command [ LPUSH {}:{} ] failed. Invalid reply.", key, value);
		return false;
	}

	debug("Success to execute command [ LPUSH {}:{} ].", key, value);
	return true;
}

bool RedisManager::lpop(const std::string& key, std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "LPOP %s", key.c_str()) };
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
		error("Execute command [ LPOP {}:{} ] failed! Empty or nil reply.", key, value);
		return false;
	}

	value = reply->str;
	debug("Success to execute command [ LPOP {}:{} ].", key, value);
	return true;
}

bool RedisManager::rpush(const std::string& key, const std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "RPUSH %s %s", key.c_str(), value.c_str()) };
	if (reply == nullptr) {
		error("Execute command [ RPUSH {}:{} ] failed! Empty or nil reply.", key, value);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
		error("Execute command [ RPUSH {}:{} ] failed! Invalid reply.", key, value);
		return false;
	}

	debug("Success to execute command [ RPUSH {}:{} ].", key, value);
	return true;
}

bool RedisManager::rpop(const std::string& key, std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis connection pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "RPOP %s", key.c_str()) };
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
		error("Execute command [ RPOP {}:{} ] failed! Empty or nil reply.", key, value);
		return false;
	}

	value = reply->str;
	debug("Success to execute command [ RPOP {}:{} ].", key, value);
	return true;
}

bool RedisManager::hset(const std::string& key, const std::string& hkey, const std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str()) };
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
		error("Execute command [ HSET {} {} {} ] failed! Invalid reply.", key, hkey, value);
		return false;
	}
	debug("Success to execute command [ HSET {} {} {} ].", key, hkey, value);
	return true;
}

bool RedisManager::hset(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return false;
	}

	const char* argv[4];
	size_t argvlen[4];
	argv[0] = "HSET";
	argvlen[0] = 4;
	argv[1] = key;
	argvlen[1] = strlen(key);
	argv[2] = hkey;
	argvlen[2] = strlen(hkey);
	argv[3] = hvalue;
	argvlen[3] = hvaluelen;

	RedisReply reply{ (redisReply*)redisCommandArgv(conn, 4, argv, argvlen) };
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
		error("Execute command [ HSET {} {} {} ] failed! Invalid reply.", key, hkey, hvalue);
		return false;
	}
	debug("Success to execute command [ HSET {} {} {} ].", key, hkey, hvalue);
	return true;
}

std::string RedisManager::hget(const std::string& key, const std::string& hkey)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return "";
	}

	const char* argv[3];
	size_t argvlen[3];
	argv[0] = "HGET";
	argvlen[0] = 4;
	argv[1] = key.c_str();
	argvlen[1] = key.length();
	argv[2] = hkey.c_str();
	argvlen[2] = hkey.length();

	RedisReply reply{ (redisReply*)redisCommandArgv(conn, 3, argv, argvlen) };
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
		error("Execute command [ HGET {} {} ] failed! Empty or nil reply.", key, hkey);
		return "";
	}
	std::string value = reply->str;
	debug("Success to execute command [ HGET {} {} ].", key, hkey);
	return value;
}

bool RedisManager::del(const std::string& key)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "DEL %s", key.c_str()) };
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
		error("Execute command [ DEL {} ] failed! Invalid reply.", key);
		return false;
	}
	debug("Success to execute command [ DEL {} ].", key);
	return true;
}

bool RedisManager::contains(const std::string& key)
{
	auto conn = _pool->get();
	if (!conn) {
		error("Connection failed. Redis Connection Pool has been stopped.");
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "exists %s", key.c_str())};
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER || reply->integer == 0) {
		debug("Key {} does not exist.", key);
		return false;
	}
	debug("Key {} exists.", key);
	return true;
}

void RedisManager::close()
{
	_pool->close();
}
