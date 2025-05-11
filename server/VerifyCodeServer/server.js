const grpc = require('@grpc/grpc-js')
const { v4: uuidv4 } = require('uuid')
const message_proto = require('./proto')
const const_module = require('./ulti')
const email_module = require('./email')
const redis_module = require('./redis')

async function getVerifyCode(call, callback) {
    console.log("email is", call.request.email);
    try {
        let query_res = await redis_module.getRedis(const_module.code_prefix + call.request.email);
        console.log("query_res is", query_res);

        // 若为空, 则说明不存在该键, 生成验证码
        let uuid = query_res;
        if (query_res == null) {
            uuid = uuidv4();
            
            // 截取前4位
            if (uuid.length > 4) {
                uuid = uuid.substring(0, 4);
            }

            // 设置 email: uuid 和 expire
            let bres = await redis_module.setRedisExpire(const_module.code_prefix + call.request.email, uuid, 300);
            if (!bres) {
                callback(null, { email: call.request.email, error: const_module.Errors.RedisErr });
                return;
            }
        }

        console.log("uuid is", uuid);
        let text = "您的验证码为" + uuid + ", 请在三分钟内完成注册";
        let mailOptions = {
            from: '2758282037@qq.com',
            to: call.request.email,
            subject: '验证码',
            text: text
        };

        let send_res = await email_module.sendMail(mailOptions);
        console.log("send res is", send_res);

        callback(null, { email: call.request.email, error: const_module.Errors.Success });
    }
    catch (error) {
        console.log("catch error is", error);
        callback(null, { email: call.request.email, error: const_module.Errors.Exception });
    }
}

function main() {
    var server = new grpc.Server();

    // 添加服务:　获取验证码
    server.addService(message_proto.GetVerifyCodeService.service, { getVerifyCode: getVerifyCode });

    // 绑定并运行
    server.bindAsync('0.0.0.0:50051', grpc.ServerCredentials.createInsecure(), (err, port) => {
        if(err) {
            console.log('Server bind failed: ', err);
            process.exit(1);
        }
        console.log('grpc server started.');
    });
}

main()