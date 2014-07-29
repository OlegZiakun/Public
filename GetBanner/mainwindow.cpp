/*
   Copyright (C) Oleg Ziakun
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMovie>
#include <QApplication>
#include "Def.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        connMgr(NULL)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete connMgr;
    delete movie;
}

void MainWindow::on_connectButton_clicked()
{
    if (!connMgr)
    {
        connMgr = new ConnectionManager;

        connect(connMgr, SIGNAL(signalTextTo(QString)), this, SLOT(slotDisplayText(QString)));
        connect(connMgr, SIGNAL(signalImageTo(QString)), this, SLOT(slotDisplayImage(QString)));

        movie = new QMovie(QApplication::applicationDirPath()+ "/" + QString(SPINNER_FILE_NAME));
    }

    if(connMgr->state == ConnectionManager::EBusy)
        ui->bannerLabel->setText(BUSY_WARNING);
    else
    {
        connMgr->SetupConnection(INITIAL_SERVER, INITIAL_PORT);
        connMgr->state = ConnectionManager::EBusy;

        ui->spinnerLabel->setMovie(movie);
        movie->start();
    }
}


void MainWindow::slotDisplayText(QString str)
{
    ui->bannerLabel->setText(str);
    StopSpinner();
}

void MainWindow::slotDisplayImage(QString data)
{
    QString base64ImageTagBefore("<img src=\"data:image/png;base64,{");
    QString base64ImageTagAfter("}\">");

    ui->bannerLabel->setText(base64ImageTagBefore + data + base64ImageTagAfter);

    StopSpinner();
}

void MainWindow::StopSpinner(void)
{
    movie->stop();
    ui->spinnerLabel->clear();
    connMgr->state = ConnectionManager::EReady;
}

