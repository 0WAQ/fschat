#ifndef _LOGICSYSTEM_H_
#define _LOGICSYSTEM_H_

#include "ulti.h"

/**
 * @brief 
 */
class LogicSystem : public Singleton<LogicSystem>
{
public:

	friend class Singleton<LogicSystem>;

private:

	LogicSystem();

public:
	
	void registerGet(std::string url, HttpHandler handler);
	bool handleGet(std::string url, std::shared_ptr<HttpConnection> conn);

private:
	std::unordered_map<std::string, HttpHandler> _post_handlers;
	std::unordered_map<std::string, HttpHandler> _get_handlers;
};

#endif // _LOGICSYSTEM_H_