#ifndef _LOGICSYSTEM_H_
#define _LOGICSYSTEM_H_

#include <unordered_map>

#include "base/ulti.h"
#include "base/singleton.h"

/**
 * @brief ����ע��ͻ�ȡ http �����ִ�к���
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