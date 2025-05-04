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
	// ����һ�� connection, ��Ϊ�����һ�� io_context
	auto& io_context = AsioIOContextPool::GetInstance().getIOContext();
	std::shared_ptr<HttpConnection> conn = std::make_shared<HttpConnection>(io_context);

	// ��ʼ����
	auto self = shared_from_this();
	_acceptor.async_accept(conn->socket(), [conn, self](beast::error_code ec) {
			try {
				// ��������������, ��������
				if (ec) {
					// TODO: ��ӡ��־

					self->start();
					return;
				}

				// TODO: ����������, ���Ҵ��� HttpConncetion ����������
				conn->start();
			
				// ��������
				self->start();
			}
			catch (std::exception& e) {
			
			}
		});
}

GateServer::~GateServer()
{
}
