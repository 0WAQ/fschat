#ifndef _VERIFYRPCCLIENT_H_
#define _VERIFYRPCCLIENT_H_

#include <grpcpp/grpcpp.h>

#include "ulti.h"
#include "message.grpc.pb.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVerifyCodeReq;
using message::GetVerifyCodeRsp;
using message::GetVerifyCodeService;

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
	std::unique_ptr<GetVerifyCodeService::Stub> _stub;
};

#endif // _VERIFYRPCCLIENT_H_