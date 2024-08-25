#include "httpmgr.h"

HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::sig_http_finish, &HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);

    // 设置Http包的内容
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

    // 获取指向自身的智能指针，防止引用计数不同步
    auto self = shared_from_this();

    // 发送请求信息，获取回复
    QNetworkReply *reply = _manager.post(request, data);
    connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod]() {
        // 有错误，结束HTTP请求
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }

        // 无错误
        QString res = reply->readAll();
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if (mod == Modules::REGISTERMOD) {
        // 发送信号，通知指定模块的HTTP响应结束了
        emit sig_reg_mod_finish(id, res ,err);
    }
}
