#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "global.h"
#include "singleton.h"

#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

/**
 * @brief http 管理类
 * @attention CRTP
 */
class HttpManager : public QObject,
                    public Singleton<HttpManager>
{
    Q_OBJECT

private:
    /**
     * @brief Singleton::GetInstance 会构造 HttpManager 对象,
     * 		  将 Singleton 设置为友元类
     */
    friend class Singleton<HttpManager>;

    HttpManager();

public:
    /**
     * @brief SendHttpRequest 发送 http 请求
     * @param url
     * @param json
     * @param id
     * @param mod 发送 http 请求的模块
     */
    void SendHttpRequest(QUrl url, QJsonObject json, RequestId id, Modules mod);

private slots:
    /**
     * @brief 向 mod 模块发送信号
     */
    void slot_http_request_finish(RequestId id, QString res, ErrorCode ec, Modules mod);

signals:
    void sig_http_request_finish(RequestId id, QString res, ErrorCode ec, Modules mod);

    void sig_mod_register_http_request_finish(RequestId id, QString res, ErrorCode ec);

public:
    ~HttpManager();

private:
    QNetworkAccessManager _manager;
};

#endif // HTTPMANAGER_H
