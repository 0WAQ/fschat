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
				// ��������������, ��������
				if (ec) {
					// TODO: ��ӡ��־
					self->start();
					return;
				}

				// TODO: ����������, ���Ҵ��� HttpConncetion ����������
				std::make_shared<HttpConnection>(std::move(self->_socket))->start();
			
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
