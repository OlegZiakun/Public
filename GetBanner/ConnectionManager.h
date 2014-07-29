/*
   Copyright (C) Oleg Ziakun
*/

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtCore/QDebug>
#include <QWidget>
#include <QTcpSocket>
#include "Parser.h"

class ConnectionManager: public QWidget
{
    Q_OBJECT

public:

    enum EStates
    {
        EReady = 0,
        EBusy,
    };

    enum EConnectionTypes
    {
        ERedirect = 0,
        EDataRequest,
        EContinueDataRequest
    };

    enum EBannerTypes
    {
        EUnknown = -1,
        ENone,
        EText,
        EImage,
        EContinue
    };

    ConnectionManager(QWidget* parent = 0);
    ~ConnectionManager();

public:
    void SetupConnection(const QString& serverName, int port);
    void SendImageData(QString data);
    void SendText(QString str);

private:

    void SendRequest(const QString& requestStr);
    void HandleResponse(void);
    void HandleBannerData(int respType = EDataRequest);
    void Redirection(void);
    void DisplayBanner(int type, QString& dataStr);
    QString GetResponse(void) const;

public:
    EStates state;

private:
    QTcpSocket* tcpSocket;
    int actionCounter;
    QStringList strRequests;
    QString dataResponseStr;

signals:
    void signalImageTo(QString data);
    void signalTextTo(QString str);

private slots:
    void slotReadyRead(void);
    void slotError(QAbstractSocket::SocketError);
    void slotConnected(void);

};

#endif // CONNECTIONMANAGER_H
