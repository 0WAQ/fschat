#include "MysqlDAO.h"
#include "base/ConfigManager.h"

MysqlDAO::MysqlDAO()
{
	ConfigManager& config = ConfigManager::GetInstance();
	const std::string& host = config["MySQL"]["Host"];
	const std::string& port = config["MySQL"]["Port"];
	const std::string& user = config["MySQL"]["User"];
	const std::string& passwd = config["MySQL"]["Passwd"];
	const std::string& schema = config["MySQL"]["Schema"];
	// TODO: 连接池大小
	_pool.reset(new SqlConnectionPool(host + ":" + port, user, passwd, schema, 5));
}

std::pair<int, int> MysqlDAO::regUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	auto conn = _pool->get();
	if (!conn) {
		return { 0, -1 };
	}

	try {
		std::unique_ptr<sql::PreparedStatement> stmt{
			conn->conn()->prepareStatement("CALL reg_user(?,?,?,@curr_uid,@error_code)")
		};
		stmt->setString(1, name);
		stmt->setString(2, email);
		stmt->setString(3, pwd);
		stmt->execute();

		std::unique_ptr<sql::Statement> stmt_res{ conn->conn()->createStatement() };
		std::unique_ptr<sql::ResultSet> rs{
			stmt_res->executeQuery("SELECT @curr_uid AS uid, @error_code AS ec")
		};
		if (rs->next()) {
			int curr_uid = rs->getInt("uid");
			int ec = rs->getInt("ec");
			_pool->ret(std::move(conn));
			return { curr_uid, ec };
		}

		_pool->ret(std::move(conn));
		return { 0, -1 };
	}
	catch (sql::SQLException& e) {
		_pool->ret(std::move(conn));
		error("SQLException: {} (MySQL error code: {}, SQLState: {}).", e.what(), e.getErrorCode(), e.getSQLState());
		return { 0, -1 };
	}
}

bool MysqlDAO::checkEmail(const std::string& name, const std::string& email)
{
	return false;
}

bool MysqlDAO::updatePasswd(const std::string& name, const std::string& passwd)
{
	return false;
}

bool MysqlDAO::checkPasswd(const std::string& name, const std::string& passwd, UserInfo& userinfo)
{
	return false;
}
