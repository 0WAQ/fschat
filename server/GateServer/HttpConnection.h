#ifndef _HTTPCONNECTION_H_
#define _HTTPCONNECTION_H_

#include "ulti.h"

#include <chrono>

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:

	HttpConnection(boost::asio::io_context& ioc);

	void start();

	HttpRequest& request() { return _request; }
	HttpResponse& response() { return _response; }
	tcp::socket& socket() { return _socket; }
	std::unordered_map<std::string, std::string>& params() { return _params; }

	~HttpConnection();

private:

	/**
	 * @brief 解析查询参数
	 */
	void preParseGetParam();

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

	std::string _url;
	std::unordered_map<std::string, std::string> _params;
};

#endif // _HTTPCONNECTION_H_