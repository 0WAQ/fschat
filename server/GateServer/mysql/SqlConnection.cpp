#include "SqlConnection.h"

SqlConnection::SqlConnection(sql::Connection* conn, int64_t last_access_time)
	: _conn(conn)
	, _last_access_time(last_access_time)
{
}

SqlConnection::~SqlConnection()
{
	delete _conn;
	_conn = nullptr;
}
