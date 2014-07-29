/*
   Copyright (C) Oleg Ziakun
*/

#include "ConnectionManager.h"
#include "mainwindow.h"
#include "Def.h"

ConnectionManager::ConnectionManager(QWidget* parent):
    QWidget(parent),
    state(EReady),
    tcpSocket(NULL),
    actionCounter(0)
{
    strRequests << REDIRECT_REQUEST;
    strRequests << DATA_REQUEST;
}

ConnectionManager::~ConnectionManager()
{
    if(tcpSocket)
    {
        tcpSocket->close();
        delete tcpSocket;
    }
}

void ConnectionManager::slotReadyRead(void)
{
    HandleResponse();
}

void ConnectionManager::slotError(QAbstractSocket::SocketError err)
{
    if(err == QAbstractSocket::HostNotFoundError || err == QAbstractSocket::ConnectionRefusedError || err == QAbstractSocket::NetworkError ||  err == QAbstractSocket::SocketTimeoutError)
        SetupConnection(INITIAL_SERVER, INITIAL_PORT);
}

void ConnectionManager::slotConnected(void)
{
    SendRequest(strRequests[actionCounter]);
}

void ConnectionManager::SetupConnection(const QString& serverName, int port)
{
    if(tcpSocket)
    {
        tcpSocket->close();
        tcpSocket->open(QIODevice::ReadWrite);
    }
    else
    {
        tcpSocket  = new QTcpSocket(this);

        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
        connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
        connect(tcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
    }

    tcpSocket->connectToHost(serverName, port);
}

void ConnectionManager::SendRequest(const QString& requestStr)
{
    tcpSocket->write(requestStr.toAscii());
}

void ConnectionManager::HandleResponse(void)
{
    switch(actionCounter)
    {
    case ERedirect:
        Redirection();
        break;

    case EDataRequest:
        HandleBannerData();
        break;
    case EContinueDataRequest:
        HandleBannerData(EContinue);
        break;
    }
}

QString ConnectionManager::GetResponse(void) const
{
    QByteArray byteArray;

    byteArray = tcpSocket->readAll();
    QString responseStr(byteArray);

    return responseStr;
}

void ConnectionManager::Redirection(void)
{
    QString responseStr(GetResponse());
    Parser result(responseStr);

    if(result.GetKeyValue(RESULT_KEY) == ERROR_VAL)
    {
        //handle an error here
        qWarning(ERROR_WARNING);
        return;
    }

    QString server(result.GetKeyValue(SERVER_KEY));
    int port = result.GetKeyValue(PORT_KEY).toInt();

    ++actionCounter;

    SetupConnection(server, port);
}

void ConnectionManager::HandleBannerData(int respType)
{
    QString responseStr(GetResponse());

    if(respType == EContinue)
        dataResponseStr += responseStr;
    else
        dataResponseStr = responseStr;

    {
        Parser bannerTokenRecognize(dataResponseStr, BANNER_TOKEN_SEP);
        int bannerToken = bannerTokenRecognize.GetResponseValue(Parser::ELeft).toInt();

        if(bannerToken != BANNER_DATA)
            return;
    }

    Parser bannerRecognize(dataResponseStr);

    if(bannerRecognize.GetKeyValue(STATUS_KEY) != SUCCESS_VAL)
    {
        //handle an error here
        qWarning(ERROR_WARNING);
        return;
    }

    int type = EUnknown;
    QString dataStr = NULL;
    QString typeStr (bannerRecognize.GetKeyValue(TYPE_KEY));

    if(bannerRecognize.IsCompleteDataReceived())
    {
        if(typeStr != NULL)
        {
            type = typeStr.toInt();

            if (type == EText)
                dataStr = bannerRecognize.GetKeyValue(TEXT_KEY);

            if (type == EImage)
                dataStr = bannerRecognize.GetKeyValue(CONTENT_BASE64_KEY);
        }

        actionCounter = ERedirect;
    }
    else
        type = EContinue;

    DisplayBanner(type, dataStr);
}

void ConnectionManager::DisplayBanner(int type, QString& dataStr)
{
    switch(type)
    {
    case EUnknown:
        qWarning(ERROR_WARNING);//handle an error here
        break;
    case ENone:
        SendText(QString(NO_BANNER_FOUND_WARNING));
        break;
    case EText:
    {
        Parser parser(DECODE_WEB_STR);
        parser.DecodeWebStr(dataStr);
        SendText(dataStr);
    }
        break;
    case EImage:
        SendImageData(dataStr);
        break;
    case EContinue:
        actionCounter = EContinueDataRequest;
        break;
    }
}

void ConnectionManager::SendImageData(QString data)
{
    emit signalImageTo(data);
}

void ConnectionManager::SendText(QString str)
{
    emit signalTextTo(str);
}


