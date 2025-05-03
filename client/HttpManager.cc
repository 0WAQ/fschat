#include "HttpManager.h"

HttpManager::HttpManager()
{
    // 连接信号与槽函数
    connect(this, &HttpManager::sig_http_request_finish, this, &HttpManager::slot_http_request_finish);
}

void HttpManager::SendHttpRequest(QUrl url, QJsonObject json, RequestId id, Modules mod)
{
    // 序列化 json 对象为字节流
    QByteArray data = QJsonDocument(json).toJson();

    // 构造 http 请求
    QNetworkRequest request{ url };

    // 设置 http 请求头
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.size()));

    // 发送 http 请求
    QNetworkReply *reply = _manager.post(request, data);

    // 等待 reply 发送 finish 信号, 处理 http 响应
    auto self = this;   // TAG: shared_from_this 有个要求就是对象必须要由 shared_ptr 管理, 唯一单例没有必要
    QObject::connect(reply, &QNetworkReply::finished, [self, reply, id, mod]() {
        // 处理错误情况
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();

            // 发送信号, 通知完成
            emit self->sig_http_request_finish(id, "", ErrorCode::EC_NETWORK, mod);
            reply->deleteLater(); // 延迟释放(可能会被底层的事节循环引用)
            return;
        }

        // 无错误
        QString res = reply->readAll();

        // 发送信号
        emit self->sig_http_request_finish(id, res, ErrorCode::EC_SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

void HttpManager::slot_http_request_finish(RequestId id, QString res, ErrorCode ec, Modules mod)
{
    // 向 mod 模块发送信号
    switch (mod) {
    case Modules::MOD_REGISTER:
        emit sig_mod_register_http_request_finish(id, res, ec);
        break;

    default:
        break;
    }
}

HttpManager::~HttpManager()
{

}

