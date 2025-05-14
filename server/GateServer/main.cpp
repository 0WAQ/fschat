#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <hiredis/hiredis.h>

#include <cassert>

#include "base/ulti.h"
#include "base/ConfigManager.h"
#include "redis/RedisManager.h"
#include "mysql/MysqlManager.h"
#include "GateServer.h"
#include "LogicSystem.h"
#include "HttpConnection.h"
#include "GetVerifyCodeRpcClient.h"

int main()
{
	// 获取验证码
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
				response_json["error"] = ErrorCode::EC_INVALID_JSON;
				beast::ostream(conn->response().body()) << response_json.toStyledString();

				warn("Parse JSON data failed.");
				return true;
			}

			// 提取 email 字段
			if (!request_json.isMember("email")) {
				response_json["error"] = ErrorCode::EC_INVALID_JSON;
				beast::ostream(conn->response().body()) << response_json.toStyledString();

				warn("Invalid JSON data: No \'Email\' Field.");
				return true;
			}

			auto email = request_json["email"].asString();
			// 发起 rpc 调用
			GetVerifyCodeRsp response = GetVerifyCodeRpcClient::GetInstance().getVerifyCode(email);
			response_json["error"] = response.error();
			response_json["email"] = request_json["email"]; // TODO: 应替换为 response.email()
			beast::ostream(conn->response().body()) << response_json.toStyledString();

			debug("email is {}", email);
			return true;
		});

	// 用户注册
	LogicSystem::GetInstance().registerPost("/register",
		[](std::shared_ptr<HttpConnection> conn) {

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
				response_json["error"] = ErrorCode::EC_INVALID_JSON;
				beast::ostream(conn->response().body()) << response_json.toStyledString();

				warn("Parse JSON data failed.");
				return true;
			}

			const std::string& user = request_json["user"].asString();
			const std::string& email = request_json["email"].asString();
			const std::string& passwd = request_json["passwd"].asString();

			// 去 redis 中查找邮箱对应的验证码
			std::string verify_code;
			bool b_success = RedisManager::GetInstance()
				.get(CODE_PREFIX + email, verify_code);
			if (!b_success) {
				response_json["error"] = ErrorCode::EC_REGISTER_EXPIRED_VERIFY_CODE;
				beast::ostream(conn->response().body()) << response_json.toStyledString();
				
				debug("Invalid email or Expired verify code.");
				return true;
			}

			// 判断与用户输入的验证码是否一致
			if (verify_code != request_json["verify_code"].asString()) {
				response_json["error"] = ErrorCode::EC_REGISTER_VERIFY_CODE_ERROR;
				beast::ostream(conn->response().body()) << response_json.toStyledString();

				debug("Error verify code.");
				return true;
			}

			// 向数据库中注册用户
			auto [uid, ec] = MysqlManager::GetInstance().regUser(user, email, passwd);
			if (ec == -1) {
				debug("MySQL error");
				response_json["error"] = ErrorCode::EC_REGISTER_MYSQL_EXCEPTION;
				return true;
			}
			if (uid == 0 && ec >= 0) {
				if (ec == 1) {
					debug("User exist.");
					response_json["error"] = ErrorCode::EC_REGISTER_USER_EXIST;
				}
				else if (ec == 2) {
					debug("Email exist.");
					response_json["error"] = ErrorCode::EC_REGISTER_EMAIL_EXIST;
				}
				beast::ostream(conn->response().body()) << response_json.toStyledString();
				return true;
			}

			response_json["uid"] = uid;
			response_json["error"] = ErrorCode::EC_REGISTER_SUCCESS;
			beast::ostream(conn->response().body()) << response_json.toStyledString();
			return true;
		});

	// 启动服务
	RedisManager::GetInstance();
	MysqlManager::GetInstance();

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