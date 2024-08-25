#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>

#include <iostream>
#include <memory>
#include <mutex>
#include <functional>

#include <Qstyle>
#include <QRegularExpression>
#include <QByteArray>
#include <QJsonDocument>
#include <QNetworkReply>

/**
 * @brief  刷新qss样式
*/
extern std::function<void(QWidget*)> repolish;

enum ReqId {
    ID_GET_VARIFY_CODE = 1001,
    ID_GET_USER = 1002,
};

enum Modules {
    REGISTERMOD = 0,
};

enum ErrorCodes {
    SUCCESS = 0,
    ERR_JSON= 1,
    ERR_NETWORK= 2,
};

#endif // GLOBAL_H
