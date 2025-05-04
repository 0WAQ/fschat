#include "HttpConnection.h"
#include "LogicSystem.h"

HttpConnection::HttpConnection(boost::asio::io_context& ioc)
	: _socket(ioc)
{
}

void HttpConnection::start()
{
	auto self = shared_from_this();
	http::async_read(_socket, _buffer, _request,
		[self](beast::error_code ec, std::size_t size) {
			try {
				if (ec) {
					// TODO: 打印日志
					std::cout << "http read err is " << ec.what() << std::endl;
					return;
				}

				boost::ignore_unused(size);
				self->handleRequst();
				self->checkDeadline();	// 启动超时检测
				self->writeResponse();
			}
			catch (std::exception& e) {
				// TODO: 打印日志
				std::cout << "exception is " << e.what() << std::endl;
			}
		});

}

HttpConnection::~HttpConnection()
{
}

void HttpConnection::preParseGetParam()
{
	auto uri = _request.target();
	 
	// 参数开始的位置('?')
	auto query_pos = uri.find('?');
	if (query_pos == std::string::npos) {
		_url = uri;
		return;
	}

	_url = uri.substr(0, query_pos);
	std::string query = uri.substr(query_pos + 1);
	std::string key{ "" };
	std::string value{ "" };

	// 解析查询参数
	size_t pos = 0;
	while ((pos = query.find('&')) != std::string::npos) {
		std::string pair = query.substr(0, pos);
		size_t eq_pos = pair.find('=');

		if (eq_pos != std::string::npos) {
			key = urlDecode(pair.substr(0, eq_pos));
			value = urlDecode(pair.substr(eq_pos + 1));
			_params[key] = value;
		}
		query.erase(0, pos + 1);
	}

	// 处理最后一个参数对
	if (!query.empty()) {
		size_t eq_pos = query.find('=');
		if (eq_pos != std::string::npos) {
			key = urlDecode(query.substr(0, eq_pos));
			value = urlEncode(query.substr(eq_pos + 1));
			_params[key] = value;
		}
	}
}

void HttpConnection::checkDeadline()
{
	auto self = shared_from_this();
	_deadline.async_wait([self](beast::error_code ec) {
			// TODO: 出错也应该关?
			if (!ec) {
				// TODO: 服务端主动关闭会进入 time_wait 状态
				self->_socket.close(ec);
			}
		});
}

void HttpConnection::writeResponse()
{
	auto self = shared_from_this();
	
	_response.content_length(_response.body().size());
	http::async_write(_socket, _response,
		[self](beast::error_code ec, std::size_t size) {
			self->_socket.shutdown(tcp::socket::shutdown_send, ec);
			self->_deadline.cancel();
		});
}

void HttpConnection::handleRequst()
{
	_response.version(_request.version());
	_response.keep_alive(false);
	_response.set(http::field::content_type, "text/plain");

	if (_request.method() == http::verb::get)
	{
		// 解码并解析参数
		preParseGetParam();

		bool success = LogicSystem::GetInstance().handleGet(_url, shared_from_this());
		if (!success) {
			_response.result(http::status::not_found);
			beast::ostream(_response.body()) << "url not found\r\n";
			writeResponse();
			return;
		}

		_response.result(http::status::ok);
		_response.set(http::field::server, "GateServer");
		writeResponse();
		return;
	}

	if (_request.method() == http::verb::post)
	{
		bool success = LogicSystem::GetInstance().handlePost(_request.target(),
							shared_from_this());
		if (!success) {
			_response.result(http::status::not_found);
			beast::ostream(_response.body()) << "url not found\r\n";
			writeResponse();
			return;
		}

		_response.result(http::status::ok);
		_response.set(http::field::server, "GateServer");
		writeResponse();
		return;
	}
}
