#include "RedisManager.h"
#include "base/ConfigManager.h"

// TODO: 待扩展为池
RedisManager::RedisManager()
{
	auto& config = ConfigManager::GetInstance();
	auto host = config["Redis"]["Host"];
	auto port = config["Redis"]["Port"];
	auto pwd = config["Redis"]["Passwd"];
	// TODO: pool_size 读配置文件
	_pool.reset(new RedisConnectionPool(5, host, std::atoi(port.c_str()), pwd));
}

bool RedisManager::get(const std::string& key, std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "GET %s", key.c_str())  };
	if (reply == nullptr) {
		// TODO: 打印日志
		std::cout << "[ Get " << key << " ] failed" << std::endl;
		return false;
	}

	if (reply->type != REDIS_REPLY_STRING) {
		std::cout << "[ Get " << key << " ] failed" << std::endl;
		return false;
	}

	value = reply->str;

	// TODO: 打印日志
	std::cout << "Success to execute command [ Get " << key << "]" << std::endl;
	return true;
}

bool RedisManager::set(const std::string& key, const std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "SET %s %s", key.c_str(), value.c_str()) };

	if (reply == nullptr) {
		// TODO: 打印日志
		std::cout << "Execute command [ SET " << key << " " << value << " ] failed!" << std::endl;
		return false;
	}

	if (!(reply->type == REDIS_REPLY_STATUS)
		&& (strcmp(reply->str, "OK") == 0
			|| strcmp(reply->str, "ok")))
	{
		// TODO: 打印日志
		std::cout << "Execute command [ SET " << key << " " << value << " ] failed!" << std::endl;
		return false;
	}

	std::cout << "Execute command [ SET " << key << " " << value << " ] success!" << std::endl;
	return true;
}

bool RedisManager::auth(const std::string& passwd)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "AUTH %s", passwd.c_str()) };
	if (reply->type == REDIS_REPLY_ERROR) {
		// TODO: 打印日志
		// std::cout << "认证失败!" << std::endl;
		return false;
	}

	// TODO: 打印日志
	// std::cout << "认证成功" << std::endl;
	return true;
}

bool RedisManager::lpush(const std::string& key, const std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "LPUSH %s %s", key.c_str(), value.c_str()) };
	if (reply == nullptr) {
		// TODO: 打印日志
		std::cout << "Execute command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
		// TODO: 打印日志
		std::cout << "Execute command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		return false;
	}

	// TODO: 打印日志
	std::cout << "Execute command [ LPUSH " << key << "  " << value << " ] success ! " << std::endl;
	return true;
}

bool RedisManager::lpop(const std::string& key, std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "LPOP %s", key.c_str()) };
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
		// TODO: 打印日志
		std::cout << "Execute command [ LPOP " << key << "  " << value << " ] failure ! " << std::endl;
		return false;
	}

	value = reply->str;

	// TODO: 打印日志
	std::cout << "Execute command [ LPOP " << key << "  " << value << " ] success ! " << std::endl;
	return true;
}

bool RedisManager::rpush(const std::string& key, const std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "RPUSH %s %s", key.c_str(), value.c_str()) };
	if (reply == nullptr) {
		// TODO: 打印日志
		std::cout << "Execute command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
		// TODO: 打印日志
		std::cout << "Execute command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		return false;
	}

	// TODO: 打印日志
	std::cout << "Execute command [ RPUSH " << key << "  " << value << " ] success ! " << std::endl;
	return true;
}

bool RedisManager::rpop(const std::string& key, std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "RPOP %s", key.c_str()) };
	if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
		// TODO: 打印日志
		std::cout << "Execute command [ RPOP " << key << "  " << value << " ] failure ! " << std::endl;
		return false;
	}

	value = reply->str;

	// TODO: 打印日志
	std::cout << "Execute command [ RPOP " << key << "  " << value << " ] success ! " << std::endl;
	return true;
}

bool RedisManager::hset(const std::string& key, const std::string& hkey, const std::string& value)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str()) };
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
		// TODO: 打印日志
		std::cout << "Execute command [ HSet " << key << "  " << hkey << "  " << value << " ] failure ! " << std::endl;
		return false;
	}
	// TODO: 打印日志
	std::cout << "Execute command [ HSet " << key << "  " << hkey << "  " << value << " ] success ! " << std::endl;
	return true;
}

bool RedisManager::hset(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
	auto conn = _pool->get();
	if (!conn) {
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
		// TODO: 打印日志
		std::cout << "Execute command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] failure ! " << std::endl;
		return false;
	}

	// TODO: 打印日志
	std::cout << "Execute command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] success ! " << std::endl;
	return true;
}

std::string RedisManager::hget(const std::string& key, const std::string& hkey)
{
	auto conn = _pool->get();
	if (!conn) {
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
		// TODO: 打印日志
		std::cout << "Execute command [ HGet " << key << " " << hkey << "  ] failure ! " << std::endl;
		return "";
	}
	std::string value = reply->str;
	// TODO: 打印日志
	std::cout << "Execute command [ HGet " << key << " " << hkey << " ] success ! " << std::endl;
	return value;
}

bool RedisManager::del(const std::string& key)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "DEL %s", key.c_str()) };
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
		// TODO: 打印日志
		std::cout << "Execute command [ Del " << key << " ] failure ! " << std::endl;
		return false;
	}

	// TODO: 打印日志
	std::cout << "Execute command [ Del " << key << " ] success ! " << std::endl;
	return true;
}

bool RedisManager::contains(const std::string& key)
{
	auto conn = _pool->get();
	if (!conn) {
		return false;
	}

	RedisReply reply{ (redisReply*)redisCommand(conn, "exists %s", key.c_str())};
	if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER || reply->integer == 0) {
		// TODO: 打印日志
		std::cout << "Not Found [ Key " << key << " ]  ! " << std::endl;
		return false;
	}
	// TODO: 打印日志
	std::cout << " Found [ Key " << key << " ] exists ! " << std::endl;
	return true;
}

void RedisManager::close()
{
	_pool->close();
}
