#ifndef _SQLCONNECTIONPOOL_H_
#define _SQLCONNECTIONPOOL_H_

#include <queue>

#include "base/ulti.h"
#include "SqlConnection.h"

/**
 * @brief SQLÁ¬½Ó³Ø
 */
class SqlConnectionPool
{
public:

	SqlConnectionPool(const std::string& url,
		const std::string& user,
		const std::string& passwd,
		const std::string& schema,
		size_t pool_size);

	std::unique_ptr<SqlConnection> get();
	void ret(std::unique_ptr<SqlConnection> conn);

	void checkConnection();

	void close();

	~SqlConnectionPool();

private:
	std::string _url;
	std::string _user;
	std::string _passwd;
	std::string _schema;

	size_t _pool_size;
	std::queue<std::unique_ptr<SqlConnection>> _pool;
	
	std::mutex _mutex;
	std::condition_variable _cond;
	std::atomic<bool> _b_stop;

	std::thread _check_thread;
};

#endif // _SQLCONNECTIONPOOL_H_