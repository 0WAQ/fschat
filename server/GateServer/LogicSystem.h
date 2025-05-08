#ifndef _LOGICSYSTEM_H_
#define _LOGICSYSTEM_H_

#include <unordered_map>

#include "base/ulti.h"
#include "base/singleton.h"

/**
 * @brief 用于注册和获取 http 请求的执行函数
 */
class LogicSystem : public Singleton<LogicSystem>
{
public:

	friend class Singleton<LogicSystem>;

private:

	LogicSystem();

public:
	
	void registerGet(std::string url, HttpHandler handler);
	void registerPost(std::string url, HttpHandler handler);

	bool handleGet(std::string url, std::shared_ptr<HttpConnection> conn);
	bool handlePost(std::string url, std::shared_ptr<HttpConnection> conn);

private:
	std::unordered_map<std::string, HttpHandler> _get_handlers;
	std::unordered_map<std::string, HttpHandler> _post_handlers;
};

#endif // _LOGICSYSTEM_H_