#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>

#include "CServer.h"
#include "LogicSystem.h"
#include "HttpConnection.h"

int main()
{
	// TODO: get_test
	LogicSystem::GetInstance().registerGet("/get_test",
		[](std::shared_ptr<HttpConnection> conn) {
			beast::ostream(conn->response().body()) << "receive get_test req";
		});

	try {
		unsigned short port = static_cast<unsigned short>(8080);
		net::io_context ioc{ 1 };
		boost::asio::signal_set signals{ ioc, SIGINT, SIGTERM };
		signals.async_wait(
			[&ioc](const boost::system::error_code &ec, int signal_number) {
				if (ec) {
					return;
				}

				ioc.stop();
			});

		std::make_shared<CServer>(ioc, port)->start();
		ioc.run();
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}