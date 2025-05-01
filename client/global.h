#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <QStyle>
#include <QRegularExpression>
#include <QByteArray>
#include <QNetworkReply>

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
    ID_GET_USER		   	= 1002,	// 注册哟用户
};

enum Modules {
    MOD_REGISTER		= 0,
};

enum ErrorCode {
    EC_SUCCESS	= 0,
    EC_PARSE_JSON_FAILED = 1,	// json 解析失败
    EC_NETWORK = 2,				// 网络错误
};

#endif // GLOBAL_H
