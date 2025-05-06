#include "RedisManager.h"

// TODO: 待扩展为池
RedisManager::RedisManager()
{
}

bool RedisManager::connect(const std::string& host, int port)
{
	_connect = redisConnect(host.c_str(), port);
	if (_connect == nullptr) {
		// TODO: 打印日志
		return false;
	}

	if (_connect && _connect->err) {
		// TODO: 打印日志
		std::cout << "connect error: " << _connect->errstr << std::endl;
		return false;
	}
	return true;
}

bool RedisManager::get(const std::string& key, std::string& value)
{
	Reply reply{ (redisReply*)redisCommand(_connect, "GET %s", key.c_str())  };
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
	Reply reply{ (redisReply*)redisCommand(_connect, "SET %s %s", key.c_str(), value.c_str()), deletor{} };

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
	Reply reply{ (redisReply*)redisCommand(_connect, "AUTH %s", passwd.c_str()), deletor{} };
	if (reply->type == REDIS_REPLY_ERROR) {
		// TODO: 打印日志
		std::cout << "认证失败!" << std::endl;
		return false;
	}

	// TODO: 打印日志
	std::cout << "认证成功" << std::endl;
	return true;
}

bool RedisManager::lpush(const std::string& key, const std::string& value)
{
	Reply reply{ (redisReply*)redisCommand(_connect, "LPUSH %s %s", key.c_str(), value.c_str()), deletor{} };
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
	Reply reply{ (redisReply*)redisCommand(_connect, "LPOP %s", key.c_str()), deletor{} };
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
	Reply reply{ (redisReply*)redisCommand(_connect, "RPUSH %s %s", key.c_str(), value.c_str()), deletor{} };
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
	Reply reply{ (redisReply*)redisCommand(_connect, "RPOP %s", key.c_str()), deletor{} };
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
	Reply reply{ (redisReply*)redisCommand(_connect, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str()), deletor{} };
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

	Reply reply{ (redisReply*)redisCommandArgv(_connect, 4, argv, argvlen), deletor{} };
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
	const char* argv[3];
	size_t argvlen[3];
	argv[0] = "HGET";
	argvlen[0] = 4;
	argv[1] = key.c_str();
	argvlen[1] = key.length();
	argv[2] = hkey.c_str();
	argvlen[2] = hkey.length();

	Reply reply{ (redisReply*)redisCommandArgv(_connect, 3, argv, argvlen), deletor{} };
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
	Reply reply{ (redisReply*)redisCommand(_connect, "DEL %s", key.c_str()), deletor{} };
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
	Reply reply{ (redisReply*)redisCommand(_connect, "exists %s", key.c_str()), deletor{} };
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
	redisFree(_connect);
}
