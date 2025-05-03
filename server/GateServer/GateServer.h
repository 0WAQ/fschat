#ifndef _GATESERVER_H_
#define _GATESERVER_H_

#include "ulti.h"

class GateServer : public std::enable_shared_from_this<GateServer>
{
public:

	GateServer(boost::asio::io_context &ctx, unsigned short port);
	
	void start();

	~GateServer();

private:
	tcp::acceptor _acceptor;
	net::io_context &_ctx;
	tcp::socket _socket;
};

#endif // _GATESERVER_H_