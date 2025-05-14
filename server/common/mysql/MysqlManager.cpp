#include "MysqlManager.h"

MysqlManager::MysqlManager()
{
}

MysqlManager::~MysqlManager()
{
}

std::pair<int, int> MysqlManager::regUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	return _dao.regUser(name, email, pwd);
}

bool MysqlManager::checkEmail(const std::string& name, const std::string& email)
{
	return false;
}

bool MysqlManager::updatePasswd(const std::string& name, const std::string& passwd)
{
	return false;
}

bool MysqlManager::checkPasswd(const std::string& name, const std::string& passwd, UserInfo& userinfo)
{
	return false;
}
