/*
   Copyright (C) Oleg Ziakun
*/

#include <QMessageBox>
#include <QDebug>
#include "sendinfo.h"

SendInfo::SendInfo(SystemInfo &si, QObject *parentObj) :
    QObject(parentObj),
    parent(parentObj),
    systemInfo(si)
{
    networkAccessManager = new QNetworkAccessManager(this);

    connect(parent, SIGNAL(signalSendInfo(QByteArray)), this, SLOT(slotPost(QByteArray)));
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(slotReplyFinished(QNetworkReply*)));
}

SendInfo::~SendInfo()
{
    if(networkAccessManager)
        delete networkAccessManager;
}

void SendInfo::slotReplyFinished(QNetworkReply *reply)
{
    progressDialog.hide();

    emit UploadFinished();

    QMessageBox msgBox;
    QString msgString;

    if(reply->error() == QNetworkReply::NoError)
        msgString = "The data has been sent.";
    else
        msgString = "Error occured (error code " + QString::number(reply->error()) + ")";

    msgBox.setText(msgString);
    msgBox.exec();
}

void SendInfo::slotReadyRead()
{
    replyStr.append(reply->readAll());
}

void SendInfo::slotError(QNetworkReply::NetworkError error)
{
    qDebug() << "error = " << error;
}

void SendInfo::slotSslErrors(const QList<QSslError>& errors)
{
    foreach(const QSslError &e,errors)
        qDebug() << "error = " << e.error();
}

void SendInfo::slotPost(const QByteArray &imageData)
{
    progressDialog.show();
    progressDialog.setMaximum(100);
    progressDialog.setValue(0);
    progressDialog.setWindowTitle("Please wait...");

    request.setRawHeader("User-Agent", "Test client");
    QString postQuery = "http://www.somewebsite.com/data"; // set your host here

    request.setUrl(QUrl(postQuery));

    QByteArray data = getData(imageData);
    QUrl dataPart;

    dataPart.setEncodedUrl(data);

    reply = networkAccessManager->post(request, data);

    setConnections();

    progressDialog.setWindowTitle("Sending data...");
}

QByteArray SendInfo::getData(const QByteArray &imageData)
{
    QByteArray data;

    data.append("?screenshot=" + imageData);
    data.append("&osinfo=" + systemInfo.getOSInfo(QSysInfo::windowsVersion()).toAscii());
    data.append("&memoryload=" + QString::number(systemInfo.getMemoryStatusEx().dwMemoryLoad).toAscii());
    data.append("&yotalmemorymb=" + QString::number(systemInfo.getMemoryStatusEx().ullTotalPhys).toAscii());
    data.append("&availmemorymb=" + QString::number(systemInfo.getMemoryStatusEx().ullAvailPhys).toAscii());
    data.append("&totalpagefilemb=" + QString::number(systemInfo.getMemoryStatusEx().ullTotalPageFile).toAscii());
    data.append("&availpagefilemb=" + QString::number(systemInfo.getMemoryStatusEx().ullAvailPageFile).toAscii());
    data.append("&totalvirtualmemorymb=" + QString::number(systemInfo.getMemoryStatusEx().ullTotalVirtual).toAscii());
    data.append("&availvirtualmemorymb=" + QString::number(systemInfo.getMemoryStatusEx().ullAvailVirtual).toAscii());

    return data;
}

void SendInfo::slotUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    progressDialog.setMaximum(bytesTotal);
    progressDialog.setValue(bytesSent);
}

void SendInfo::setConnections(void)
{
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(const QList<QSslError>&)),this, SLOT(slotSslErrors( const QList<QSslError>&)));
    connect(reply, SIGNAL(uploadProgress(qint64, qint64)),this, SLOT(slotUploadProgress (qint64, qint64)));
}
