#include "LogicSystem.h"
#include "HttpConnection.h"

LogicSystem::LogicSystem()
{
	registerGet("/get_test",
		[](std::shared_ptr<HttpConnection> conn) {
			beast::ostream(conn->_response.body()) << "receive get_test req";
		});
}

void LogicSystem::registerGet(std::string url, HttpHandler handler)
{
	_get_handlers.insert({ url, handler });
}

bool LogicSystem::handleGet(std::string url, std::shared_ptr<HttpConnection> conn)
{
	if (_get_handlers.find(url) == _get_handlers.end()) {
		// TODO: ¥Ú”°»’÷æ
		return false;
	}

	_get_handlers[url](conn);
	return true;
}