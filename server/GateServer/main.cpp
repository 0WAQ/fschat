#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>

#include "ulti.h"
#include "ConfigManager.h"
#include "GateServer.h"
#include "LogicSystem.h"
#include "HttpConnection.h"
#include "GetVerifyCodeRpcClient.h"

int main()
{
	// TODO: get_test
	LogicSystem::GetInstance().registerGet("/get_test",
		[](std::shared_ptr<HttpConnection> conn) {
			beast::ostream(conn->response().body()) << "receive get_test req\n";
			int i = 0;
			for (auto& elem : conn->params()) {
				++i;
				beast::ostream(conn->response().body()) << "param " << i << ": key=" << elem.first;
				beast::ostream(conn->response().body()) << ", value=" << elem.second << std::endl;
			}
		});

	LogicSystem::GetInstance().registerPost("/get_verify_code",
		[](std::shared_ptr<HttpConnection> conn) -> bool {
			// 获取请求体
			std::string body = beast::buffers_to_string(conn->request().body().data());
			
			// TODO: 打印日志
			std::cout << "receive body is " << body << std::endl;

			// 设置响应头
			conn->response().set(http::field::content_type, "text/json");

			Json::Value request_json;
			Json::Value response_json;
			Json::Reader reader;
		
			// 反序列化 body 为 json 对象
			if (!reader.parse(body, request_json)) {
				response_json["error"] = ErrorCode::EC_VALID_JSON;
				beast::ostream(conn->response().body()) << response_json.toStyledString();

				// TODO: 打印日志
				std::cout << "Failed to parse JSON data!" << std::endl;
				return true;
			}

			// 提取 email 字段
			if (!request_json.isMember("email")) {
				response_json["error"] = ErrorCode::EC_VALID_JSON;
				beast::ostream(conn->response().body()) << response_json.toStyledString();

				// TODO: 打印日志
				std::cout << "Invalid JSON: No \'Email\' Field" << std::endl;
				return true;
			}

			auto email = request_json["email"].asString();
			GetVerifyCodeRsp response = GetVerifyCodeRpcClient::GetInstance().getVerifyCode(email);
			response_json["error"] = response.error();
			response_json["email"] = request_json["email"]; // TODO: 待删除?
			beast::ostream(conn->response().body()) << response_json.toStyledString();

			// TODO: 打印日志
			std::cout << "email is " << email << std::endl;
			return true;
		});

	ConfigManager config = ConfigManager::GetInstance();
	unsigned short port = std::atoi(config["GateServer"]["Port"].c_str());


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

		std::make_shared<GateServer>(ioc, port)->start();
		// TODO: 打印日志
		std::cout << "GateServer listen on port: " << port << std::endl;
		ioc.run();
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}