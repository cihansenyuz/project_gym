/**
  ******************************************************************************
  * @file    postrequest.hpp
  * @author  Cihan Senyuz
  * @date    14.07.2024
  * @brief   Header for PostRequest class.
  *          This file contains the definition of the PostRequest class, which
  *          extends NetworkCore to manage HTTP POST requests for login and
  *          registration functionalities.
  ******************************************************************************
  */

#ifndef POSTREQUEST_H
#define POSTREQUEST_H

#include "networkcore.h"

class PostRequest : public NetworkCore
{
    Q_OBJECT
public:
    PostRequest(HttpManager *parent = nullptr);
    void LoginRequest(const QString &email, const QString password);
    void RegisterRequest(const QString &email, const QString password);

signals:
    void LoginAttempt(bool success);
    void RegisterAttempt(bool success);
    void ConnectionToServer();

private slots:
    void OnRegisterReplyRecieved();
    void OnLoginReplyRecieved();

private:
    QNetworkReply* GetHttpReply(const QNetworkRequest &request) override;
    HttpManager *parent_;
};

#endif // POSTREQUEST_H
