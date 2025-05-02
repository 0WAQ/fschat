#include "HttpConnection.h"
#include "LogicSystem.h"

HttpConnection::HttpConnection(tcp::socket socket)
	: _socket(std::move(socket))
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

	if (_request.method() == http::verb::get) {
		// TODO:
		bool success = LogicSystem::GetInstance().handleGet(
			_request.target(),
			shared_from_this());
		if (!success) {
			_response.result(http::status::not_found);
			beast::ostream(_response.body()) << "url not found";
			writeResponse();
			return;
		}

		_response.result(http::status::ok);
		_response.set(http::field::server, "GateServer");
		writeResponse();
		return;
	}
}
