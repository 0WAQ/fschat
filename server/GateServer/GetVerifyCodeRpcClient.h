#ifndef _VERIFYRPCCLIENT_H_
#define _VERIFYRPCCLIENT_H_

#include <grpcpp/grpcpp.h>

#include <condition_variable>
#include <memory>
#include <queue>

#include "ulti.h"
#include "singleton.h"
#include "message.grpc.pb.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVerifyCodeReq;
using message::GetVerifyCodeRsp;
using message::GetVerifyCodeService;

/**
 * @brief 
 */
class RpcConnectPool
{
public:
	RpcConnectPool(std::size_t size, std::string host, std::string port);

	void close();

	std::unique_ptr<GetVerifyCodeService::Stub> getStub();

	void returnStub(std::unique_ptr<GetVerifyCodeService::Stub> stub);

	std::size_t size() const { return _size; }

	~RpcConnectPool();

private:
	std::atomic<bool> _stop;
	std::size_t _size;
	std::string _host;
	std::string _port;
	std::queue<std::unique_ptr<GetVerifyCodeService::Stub>> _stubs;
	std::mutex _mtx;
	std::condition_variable _cond;
};

/**
 * @brief 验证码 rpc 客户端
 */
class GetVerifyCodeRpcClient : public Singleton<GetVerifyCodeRpcClient>
{
public:
	friend class Singleton<GetVerifyCodeRpcClient>;

private:
	GetVerifyCodeRpcClient();

public:
	GetVerifyCodeRsp getVerifyCode(std::string email);

private:
	std::unique_ptr<RpcConnectPool> _pool;
};

#endif // _VERIFYRPCCLIENT_H_