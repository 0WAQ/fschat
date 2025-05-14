#ifndef _ULTI_H_
#define _ULTI_H_

#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>

#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>

#include <functional>

#include "logger.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HttpConnection;
using HttpHandler = std::function<void(std::shared_ptr<HttpConnection>)>;
using HttpRequest = http::request<http::dynamic_body>;
using HttpResponse = http::response<http::dynamic_body>;

////////////////////////////////////////////////////////////

const std::string CODE_PREFIX = "code_";

////////////////////////////////////////////////////////////

// TODO: ¸ü¸ÄÎ»ÖÃ
enum ErrorCode {
	EC_SUCCESS = 0,
	EC_INVALID_JSON = 1,
	EC_RPC_FAILED = 2,
	
	EC_REGISTER_SUCCESS = 1000,
	EC_REGISTER_MYSQL_EXCEPTION = 1,
	EC_REGISTER_EXPIRED_VERIFY_CODE = 1003,
	EC_REGISTER_VERIFY_CODE_ERROR = 1004,
	EC_REGISTER_USER_EXIST = 1005,
	EC_REGISTER_EMAIL_EXIST = 1006,
	EC_REGISTER_PASSWD_ERROR = 1007,
	EC_REGISTER_EMAIL_NOT_MATCH = 1008,
	EC_REGISTER_PASSWD_UPDATE_ERROR = 1009,
	EC_REGISTER_PASSWD_INVALID = 1010
};

////////////////////////////////////////////////////////////

unsigned char toHex(unsigned char c);
unsigned char fromHex(unsigned char c);

std::string urlEncode(const std::string& s);
std::string urlDecode(const std::string& s);

////////////////////////////////////////////////////////////

class Defer
{
public:
	Defer(std::function<void()> func);
	
	~Defer();

private:
	std::function<void()> _func;
};

#endif // _ULTI_H_