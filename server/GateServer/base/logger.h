#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>
#include <vector>

#include "singleton.h"

class Logger : public Singleton<Logger>
{
public:
	friend class Singleton<Logger>;

private:

	Logger()
	{
		// TODO: 参数值
		spdlog::init_thread_pool(8192, 1);

		auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		stdout_sink->set_level(spdlog::level::debug);
		
		auto stderr_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
		stdout_sink->set_level(spdlog::level::err);

		std::vector<spdlog::sink_ptr> sinks{ stdout_sink, stderr_sink };
		_logger = std::make_shared<spdlog::async_logger>(spdlog::async_logger{
				"async-logger",
				sinks.begin(),
				sinks.end(),
				spdlog::thread_pool(),
				spdlog::async_overflow_policy::block	// TODO: 类型
			});
	}

public:
	std::shared_ptr<spdlog::async_logger>& operator->() {
		return _logger;
	}

private:
	std::shared_ptr<spdlog::async_logger> _logger;
};

template <typename T>
inline void trace(const T& msg) {
	Logger::GetInstance()->trace(msg);
}

template<typename ...Args>
inline void trace(spdlog::format_string_t<Args...> fmt, Args&& ...args) {
	Logger::GetInstance()->trace(fmt, std::forward<Args>(args)...);
}

template <typename T>
inline void debug(const T& msg) {
	Logger::GetInstance()->debug(msg);
}

template<typename ...Args>
inline void debug(spdlog::format_string_t<Args...> fmt, Args&& ...args) {
	Logger::GetInstance()->debug(fmt, std::forward<Args>(args)...);
}

template <typename T>
inline void info(const T& msg) {
	Logger::GetInstance()->info(msg);
}

template<typename ...Args>
inline void info(spdlog::format_string_t<Args...> fmt, Args&& ...args) {
	Logger::GetInstance()->info(fmt, std::forward<Args>(args)...);
}

template <typename T>
inline void warn(const T& msg) {
	Logger::GetInstance()->warn(msg);
}

template<typename ...Args>
inline void warn(spdlog::format_string_t<Args...> fmt, Args&& ...args) {
	Logger::GetInstance()->warn(fmt, std::forward<Args>(args)...);
}

template <typename T>
inline void error(const T& msg) {
	Logger::GetInstance()->error(msg);
}

template<typename ...Args>
inline void error(spdlog::format_string_t<Args...> fmt, Args&& ...args) {
	Logger::GetInstance()->error(fmt, std::forward<Args>(args)...);
}

template <typename T>
inline void critical(const T& msg) {
	Logger::GetInstance()->critical(msg);
}

template<typename ...Args>
inline void critical(spdlog::format_string_t<Args...> fmt, Args&& ...args) {
	Logger::GetInstance()->critical(fmt, std::forward<Args>(args)...);
}

#endif // _LOGGER_H_
