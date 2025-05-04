#include "GetVerifyCodeRpcClient.h"
#include "ConfigManager.h"

GetVerifyCodeRpcClient::GetVerifyCodeRpcClient()
{
	auto& config = ConfigManager::GetInstance();
	std::string host = config["VerifyCodeServer"]["Host"];
	std::string port = config["VerifyCodeServer"]["Port"];
	_pool.reset(new RpcConnectPool(5, host, port));
}

GetVerifyCodeRsp GetVerifyCodeRpcClient::getVerifyCode(std::string email)
{
	ClientContext ctx;
	GetVerifyCodeRsp response;
	GetVerifyCodeReq request;
	request.set_email(email);

	auto stub = _pool->getStub();	// 从 rpc 连接池中获取 stub
	Status status = stub->getVerifyCode(&ctx, request, &response);
	if (!status.ok()) {
		response.set_error(ErrorCode::EC_RPC_FAILED);
	}
	_pool->returnStub(std::move(stub));
	return response;
}

RpcConnectPool::RpcConnectPool(std::size_t size, std::string host, std::string port)
	: _size(size)
	, _host(host)
	, _port(port)
	, _stop(false)
{
	for (std::size_t i = 0; i < size; ++i) {
		std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port,
			grpc::InsecureChannelCredentials());
		_stubs.push(std::move(GetVerifyCodeService::NewStub(channel)));
	}
}


void RpcConnectPool::close()
{
	_stop = true;
	_cond.notify_all();
}


std::unique_ptr<GetVerifyCodeService::Stub> RpcConnectPool::getStub()
{
	std::unique_lock<std::mutex> guard{ _mtx };
	_cond.wait(guard, [this]() {
			if (_stop) {
				return true;
			}

			return !_stubs.empty();
		});

	if (_stop) {
		return nullptr;
	}

	auto stub = std::move(_stubs.front());
	_stubs.pop();
	return stub;
}


void RpcConnectPool::returnStub(std::unique_ptr<GetVerifyCodeService::Stub> stub)
{
	std::lock_guard<std::mutex> guard{ _mtx };
	if (_stop) {
		return;
	}
	_stubs.push(std::move(stub));
	_cond.notify_one();
}

RpcConnectPool::~RpcConnectPool()
{
	std::lock_guard<std::mutex> guard{ _mtx };
	close();
	while (!_stubs.empty()) {
		_stubs.pop();
	}
}
