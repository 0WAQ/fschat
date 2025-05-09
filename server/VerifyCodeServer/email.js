const nodemailer = require('nodemailer');
const config_module = require('./config');

/**
 * 创建发送邮件的代理
 */
let transport = nodemailer.createTransport({
    host: 'smtp.qq.com',
    port: 465,
    secure: true,
    auth: {
        user: config_module.email_user,
        pass: config_module.email_pass
    }
});

/**
 * 发送邮件
 * @param {*} mailOptions_
 * @returns
 */
function sendMail(mailOptions_) {
    return new Promise(function(resolve, reject) {
        transport.sendMail(mailOptions_, function(error, info) {
            if (error) {
                reject(error)
            }
            else {
                resolve(info.response);
            }
        });
    });
}

module.exports.sendMail = sendMail;