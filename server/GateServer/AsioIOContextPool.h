#ifndef _ASIOIOCONTEXTPOOL_H_
#define _ASIOIOCONTEXTPOOL_H_

#include "ulti.h"

/**
 * @brief 封装线程池 TODO: ?
 */
class AsioIOContextPool : public Singleton<AsioIOContextPool>
{
public:

	using IOContext = boost::asio::io_context;
	using Work = boost::asio::executor_work_guard<IOContext::executor_type>;
	using WorkPtr = std::unique_ptr<Work>;

	friend class Singleton<AsioIOContextPool>;

private:
	explicit AsioIOContextPool(std::size_t size = 2); /* std::thread::hardware_concurrency() */

public:

	/**
	 * @brief 使用 Round-Robin 获取一个 io_context
	 */
	boost::asio::io_context& getIOContext();

	void stop();

	~AsioIOContextPool();

private:
	std::vector<IOContext> _io_contexts;
	std::vector<WorkPtr> _works;
	std::vector<std::thread> _threads;
	std::size_t _next_io_context;
	std::atomic<bool> _stopping;
};

#endif // _ASIOIOCONTEXTPOOL_H_