#ifndef _CSERVER_H_
#define _CSERVER_H_

#include "ulti.h"

class CServer : public std::enable_shared_from_this<CServer>
{
public:

	CServer(boost::asio::io_context &ctx, unsigned short port);
	
	void start();

	~CServer();

private:
	tcp::acceptor _acceptor;
	net::io_context &_ctx;
	tcp::socket _socket;
};

#endif // _CSERVER_H_