const grpc = require('@grpc/grpc-js')
const { v4: uuidv4 } = require('uuid')
const message_proto = require('./proto')
const const_module = require('./const')
const email_module = require('./email')

async function getVerifyCode(call, callback) {
    console.log("email is ", call.request.email);

    try {
        const uniqueId = uuidv4();
        console.log("uniqueId is ", uniqueId);
        let text = '您的验证码为 ' + uniqueId + ' 请在三分钟内完成注册';

        let mailOptions = {
            from: '2758282037@qq.com',
            to: call.request.email,
            subject: '验证码',
            text: text
        };

        let response = await email_module.sendMail(mailOptions);
        console.log("send res is ", response)

        callback(null, { email: call.request.email, error: const_module.Errors.Success });
    }
    catch (error) {
        console.log('catch error is ', error);

        callback(null, { email: call.request.email, error: const_module.Errors.Exception});
    }
}

function main() {
    var server = new grpc.Server();
    server.addService(message_proto.GetVerifyCodeService.service, { getVerifyCode: getVerifyCode });
    server.bindAsync('0.0.0.0:50051', grpc.ServerCredentials.createInsecure(), (err, port) => {
        if(err) {
            console.log('Server bind failed: ', err);
            process.exit(1);
        }
        console.log('grpc server started.');
    });
}

main()