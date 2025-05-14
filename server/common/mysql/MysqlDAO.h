#ifndef _MYSQLDAO_H_
#define _MYSQLDAO_H_

#include "base/ulti.h"
#include "SqlConnectionPool.h"

// TODO: 业务类不要放在common模块中
struct UserInfo {
	std::string name;
	std::string pwd;
	int uid;
	std::string email;
};

/**
 * @brief dao层
 */
class MysqlDAO
{
public:
	MysqlDAO();

	/**
	 * @return [uid, error_code]
	 */
	std::pair<int, int> regUser(const std::string& name, const std::string& email, const std::string& pwd);
	bool checkEmail(const std::string& name, const std::string& email);
	bool updatePasswd(const std::string& name, const std::string& passwd);
	bool checkPasswd(const std::string& name, const std::string& passwd, UserInfo& userinfo);

private:
	std::unique_ptr<SqlConnectionPool> _pool;
};

#endif // _MYSQLDAO_H_