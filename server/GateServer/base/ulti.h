#ifndef _ULTI_H_
#define _ULTI_H_

#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>

#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>

#include <iostream>	// TODO: 添加日志库后删除

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HttpConnection;
using HttpHandler = std::function<void(std::shared_ptr<HttpConnection>)>;
using HttpRequest = http::request<http::dynamic_body>;
using HttpResponse = http::response<http::dynamic_body>;

////////////////////////////////////////////////////////////

// TODO: 更改位置
enum ErrorCode {
	EC_SUCCESS = 0,
	EC_VALID_JSON = 1001,
	EC_RPC_FAILED = 1002,
};

////////////////////////////////////////////////////////////

unsigned char toHex(unsigned char c);
unsigned char fromHex(unsigned char c);

std::string urlEncode(const std::string& s);
std::string urlDecode(const std::string& s);

////////////////////////////////////////////////////////////

#endif // _ULTI_H_