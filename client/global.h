#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <QStyle>
#include <QRegularExpression>
#include <QByteArray>
#include <QNetworkReply>
#include <QJsonObject>
#include <QSettings>
#include <QDir>

#include <functional>
#include <memory>
#include <iostream>
#include <mutex>

/**
 * @brief 用于刷新 qss 文件
 */
extern std::function<void(QWidget*)> repolish;

enum RequestId {
    ID_GET_VERIFY_CODE	= 1001,	// 获取验证码
    ID_REGISTER_USER    = 1002,	// 注册用户
};

enum Modules {
    MOD_REGISTER		= 0,
};

enum ErrorCode {
    EC_SUCCESS	= 0,
    EC_PARSE_JSON_FAILED = 1,	// json 解析失败
    EC_NETWORK = 2,				// 网络错误

    EC_REGISTER_SUCCESS = 1000,             // 注册成功
    EC_REGISTER_MYSQL_EXCEPTION = 1001,     // MySQL 异常
    EC_REGISTER_EXPIRED_VERIFY_CODE = 1003, // 验证码过期
    EC_REGISTER_VERIFY_CODE_ERROR = 1004,   // 验证码错误
    EC_REGISTER_USER_EXIST = 1005,          // 用户注册模块中, 用户名已存在
    EC_REGISTER_EMAIL_EXIST = 1006,         // 用户注册模块中, 邮箱已存在
};

extern QString gate_url_prefix;

#endif // GLOBAL_H
