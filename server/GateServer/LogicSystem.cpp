#include "LogicSystem.h"
#include "HttpConnection.h"

LogicSystem::LogicSystem()
{
}

void LogicSystem::registerGet(std::string url, HttpHandler handler)
{
	_get_handlers.insert({ url, handler });
}

void LogicSystem::registerPost(std::string url, HttpHandler handler)
{
	_post_handlers.insert({ url, handler });
}

bool LogicSystem::handleGet(std::string url, std::shared_ptr<HttpConnection> conn)
{
	if (_get_handlers.find(url) == _get_handlers.end()) {
		// TODO: 打印日志
		return false;
	}

	_get_handlers[url](conn);
	return true;
}

bool LogicSystem::handlePost(std::string url, std::shared_ptr<HttpConnection> conn)
{
	if (_post_handlers.find(url) == _post_handlers.end()) {
		// TODO: 打印日志
		return false;
	}
	_post_handlers[url](conn);
	return true;
}
