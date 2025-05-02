#ifndef _HTTPCONNECTION_H_
#define _HTTPCONNECTION_H_

#include "ulti.h"

#include <chrono>

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:

	friend class LogicSystem;

public:

	HttpConnection(tcp::socket socket);

	void start();
	
	HttpRequest& request() { return _request; }
	HttpResponse& response() { return _response; }

	~HttpConnection();

private:

	void checkDeadline();
	void writeResponse();
	void handleRequst();

private:

	tcp::socket _socket;
	beast::flat_buffer _buffer{ 8192 };
	HttpRequest _request;
	HttpResponse _response;
	net::steady_timer _deadline{
		_socket.get_executor(),
		std::chrono::seconds{ 60 }
	};
};

#endif // _HTTPCONNECTION_H_