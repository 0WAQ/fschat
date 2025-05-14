#ifndef _SQLCONNECTION_H_
#define _SQLCONNECTION_H_

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>

#include "base/ulti.h"
#include "base/noncopyable.h"

/**
 * @brief SQLÁ¬½Ó
 */
class SqlConnection : noncopyable
{
public:

	SqlConnection(sql::Connection* conn, int64_t last_time);

	sql::Connection* conn() { return _conn; }
	int64_t last_access_time() { return _last_access_time; }
	void set_last_access_time(int64_t time) { _last_access_time = time; }

	~SqlConnection();

private:
	sql::Connection* _conn;
	int64_t _last_access_time;
};

#endif // _SQLCONNECTION_H_