#include "AsioIOContextPool.h"

AsioIOContextPool::AsioIOContextPool(std::size_t size)
	: _io_contexts(size)
	, _works(size)
	, _next_io_context(0)
	, _stopping(false)
{
	// ���� work ����, ���� io_context ������
	for (std::size_t i = 0; i < size; ++i) {
		_works[i] = std::make_unique<Work>(boost::asio::make_work_guard(_io_contexts[i]));
	}

	// Ϊÿһ�� io_context ����һ�� thread
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

	// ֹͣ���� io_context
	for (auto& context : _io_contexts) {
		context.stop();
	}

	// �ͷ� work ����, ���� io_context �˳�
	_works.clear();

	// �ȴ��߳̽���
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
