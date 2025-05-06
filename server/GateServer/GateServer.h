#ifndef _GATESERVER_H_
#define _GATESERVER_H_

#include <memory>

#include "ulti.h"

class GateServer : public std::enable_shared_from_this<GateServer>
{
public:

	/**
	 * @brief ��ʼ�� GateServer �� һ�� Acceptor
	 */
	GateServer(boost::asio::io_context &ctx, unsigned short port);
	
	void start();

private:
	tcp::acceptor _acceptor;
	net::io_context &_ctx;
};

#endif // _GATESERVER_H_