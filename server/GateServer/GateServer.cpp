#include "GateServer.h"
#include "HttpConnection.h"

GateServer::GateServer(boost::asio::io_context& ctx, unsigned short port)
	: _ctx(ctx)
	, _acceptor(ctx, tcp::endpoint{ tcp::v4(), port })
	, _socket(ctx)
{
}

void GateServer::start()
{
	auto self = shared_from_this();
	_acceptor.async_accept(_socket, [self](beast::error_code ec) {
			try {
				// 出错后放弃该连接, 继续监听
				if (ec) {
					// TODO: 打印日志
					self->start();
					return;
				}

				// TODO: 创建新连接, 并且创建 HttpConncetion 类管理该连接
				std::make_shared<HttpConnection>(std::move(self->_socket))->start();
			
				// 继续监听
				self->start();
			}
			catch (std::exception& e) {
			
			}
		});
}

GateServer::~GateServer()
{
}
