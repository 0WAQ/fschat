#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <hiredis/hiredis.h>

#include <cassert>

#include "base/ulti.h"
#include "base/ConfigManager.h"
#include "redis/RedisManager.h"
#include "GateServer.h"
#include "LogicSystem.h"
#include "HttpConnection.h"
#include "GetVerifyCodeRpcClient.h"

// TODO: to be deleted
void testRedisManager()
{
	assert(RedisManager::GetInstance().connect("127.0.0.1", 6380));
	assert(RedisManager::GetInstance().auth("1234"));
	assert(RedisManager::GetInstance().set("blogwebsite", "llfc.club"));
	std::string value = "";
	assert(RedisManager::GetInstance().get("blogwebsite", value));
	assert(RedisManager::GetInstance().get("nonekey", value) == false);
	assert(RedisManager::GetInstance().hset("bloginfo", "blogwebsite", "llfc.club"));
	assert(RedisManager::GetInstance().hget("bloginfo", "blogwebsite") != "");
	assert(RedisManager::GetInstance().contains("bloginfo"));
	assert(RedisManager::GetInstance().del("bloginfo"));
	assert(RedisManager::GetInstance().del("bloginfo"));
	assert(RedisManager::GetInstance().contains("bloginfo") == false);
	assert(RedisManager::GetInstance().lpush("lpushkey1", "lpushvalue1"));
	assert(RedisManager::GetInstance().lpush("lpushkey1", "lpushvalue2"));
	assert(RedisManager::GetInstance().lpush("lpushkey1", "lpushvalue3"));
	assert(RedisManager::GetInstance().rpop("lpushkey1", value));
	assert(RedisManager::GetInstance().rpop("lpushkey1", value));
	assert(RedisManager::GetInstance().lpop("lpushkey1", value));
	assert(RedisManager::GetInstance().lpop("lpushkey2", value) == false);
	RedisManager::GetInstance().close();
}

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

			debug("receive body is {}", body);

			// 设置响应头
			conn->response().set(http::field::content_type, "text/json");

			Json::Value request_json;
			Json::Value response_json;
			Json::Reader reader;
		
			// 反序列化 body 为 json 对象
			if (!reader.parse(body, request_json)) {
				response_json["error"] = ErrorCode::EC_VALID_JSON;
				beast::ostream(conn->response().body()) << response_json.toStyledString();

				warn("Parse JSON data failed.");
				return true;
			}

			// 提取 email 字段
			if (!request_json.isMember("email")) {
				response_json["error"] = ErrorCode::EC_VALID_JSON;
				beast::ostream(conn->response().body()) << response_json.toStyledString();

				warn("Invalid JSON data: No \'Email\' Field.");
				return true;
			}

			auto email = request_json["email"].asString();
			GetVerifyCodeRsp response = GetVerifyCodeRpcClient::GetInstance().getVerifyCode(email);	// 发起 rpc 调用
			response_json["error"] = response.error();
			response_json["email"] = request_json["email"]; // TODO: 应替换为 response.email()
			beast::ostream(conn->response().body()) << response_json.toStyledString();

			debug("email is {}", email);
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

		info("GateServer listen on port: {}", port);
		ioc.run();
	}
	catch (std::exception& e) {
		error(e.what());
		return EXIT_FAILURE;
	}
}