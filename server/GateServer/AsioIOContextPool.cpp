#include "AsioIOContextPool.h"

AsioIOContextPool::AsioIOContextPool(std::size_t size)
	: _io_contexts(size)
	, _works(size)
	, _next_io_context(0)
	, _stopping(false)
{
	// 创建 work 对象, 保持 io_context 的运行
	for (std::size_t i = 0; i < size; ++i) {
		_works[i] = std::make_unique<Work>(boost::asio::make_work_guard(_io_contexts[i]));
	}

	// 为每一个 io_context 启动一个 thread
	for (std::size_t i = 0; i < size; ++i) {
		_threads.emplace_back([this, i]() {
				_io_contexts[i].run();
			});
	}
}

boost::asio::io_context& AsioIOContextPool::getIOContext()
{
	auto& io_context = _io_contexts[_next_io_context];
	if (++_next_io_context == _io_contexts.size()) {
		_next_io_context = 0;
	}
	return io_context;
}

void AsioIOContextPool::stop()
{
	assert(_stopping == false);
	_stopping = true;

	// 停止所有 io_context
	for (auto& context : _io_contexts) {
		context.stop();
	}

	// 释放 work 对象, 允许 io_context 退出
	_works.clear();

	// 等待线程结束
	for (auto& thread : _threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}

	_io_contexts.clear();
	_threads.clear();
}

AsioIOContextPool::~AsioIOContextPool()
{
	info("Closing AsioIOContextPool.");
	if (!_stopping) {
		stop();
	}
}
