/*
   Copyright (C) Oleg Ziakun
*/

#ifndef SENDINFO_H
#define SENDINFO_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>
#include <QProgressDialog>
#include "systeminfo.h"

class Screenshot;

class SendInfo: public QObject
{
    Q_OBJECT
public:
    explicit SendInfo(SystemInfo &si, QObject *parentObj = 0);
    ~SendInfo();

signals:
    void UploadFinished();

public slots:
    void slotPost(const QByteArray &imageData);
    void slotReplyFinished(QNetworkReply *reply);
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError error);
    void slotSslErrors( const QList<QSslError> &errors);
    void slotUploadProgress(qint64 bytesSent, qint64 bytesTotal);

public:
    QProgressDialog progressDialog;

private:
    void setConnections(void);
    QByteArray getData(const QByteArray &imageData);

private:
    QObject *parent;
    SystemInfo &systemInfo;
    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *reply;
    QNetworkRequest request;
    QString replyStr;

};

#endif // SENDINFO_H
