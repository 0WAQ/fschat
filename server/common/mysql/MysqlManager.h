#ifndef _MYSQLMANAGER_H_
#define _MYSQLMANAGER_H_

#include "base/ulti.h"
#include "base/singleton.h"
#include "MysqlDAO.h"

/**
 * @brief MySQL 管理类
 */
class MysqlManager : public	Singleton<MysqlManager>
{
public:
	friend class Singleton<MysqlManager>;

private:
	MysqlManager();

public:
	~MysqlManager();

	/**
	 * @return [uid, error_code], error_code = 0: 没有错误, 1: 用户已存在, 2: 邮箱已存在, -1: 发生错误
	 */
	std::pair<int, int> regUser(const std::string& name, const std::string& email, const std::string& pwd);
	bool checkEmail(const std::string& name, const std::string& email);
	bool updatePasswd(const std::string& name, const std::string& passwd);
	bool checkPasswd(const std::string& name, const std::string& passwd, UserInfo& userinfo);

private:
	MysqlDAO _dao;
};

#endif // _MYSQLMANAGER_H_