#include "GetVerifyCodeRpcClient.h"

GetVerifyCodeRpcClient::GetVerifyCodeRpcClient()
{
	// TODO: ¶ÁÅäÖÃÎÄ¼ş
	std::shared_ptr<Channel> channel = grpc::CreateChannel("0.0.0.0:50051",
		grpc::InsecureChannelCredentials());
	_stub = GetVerifyCodeService::NewStub(channel);
}

GetVerifyCodeRsp GetVerifyCodeRpcClient::getVerifyCode(std::string email)
{
	ClientContext ctx;
	GetVerifyCodeRsp response;
	GetVerifyCodeReq request;
	request.set_email(email);

	Status status = _stub->getVerifyCode(&ctx, request, &response);
	if (!status.ok()) {
		response.set_error(ErrorCode::EC_RPC_FAILED);
	}
	return response;
}
