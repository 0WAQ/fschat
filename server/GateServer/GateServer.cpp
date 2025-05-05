#include "GateServer.h"
#include "HttpConnection.h"
#include "AsioIOContextPool.h"

GateServer::GateServer(boost::asio::io_context& ctx, unsigned short port)
	: _ctx(ctx)
	, _acceptor(ctx, tcp::endpoint{ tcp::v4(), port })
{
}

void GateServer::start()
{
	// 从池中取一个 io_context, One connection Per thread
	auto& io_context = AsioIOContextPool::GetInstance().getIOContext();
	std::shared_ptr<HttpConnection> conn = std::make_shared<HttpConnection>(io_context); // TODO: 可以封装一个 http 连接池

	// 开始监听
	auto self = shared_from_this();
	_acceptor.async_accept(conn->socket(), [conn, self](beast::error_code ec) {
			try {
				// 出错后放弃该连接, 继续监听
				if (ec) {
					// TODO: 打印日志

					self->start();
					return;
				}

				// TODO: 创建新连接, 并且创建 HttpConncetion 类管理该连接
				conn->start();
			
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
