/*
   Copyright (C) Oleg Ziakun
*/

#include <QRadioButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::Dialog),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    mercedes.reset(new Mercedes);
    ferrari.reset(new Ferrari);

    setConnections();
}

void MainWindow::slotRun()
{
    ui->resultTextEdit->clear();

    mercedes->start();
    ferrari->start();
}

void MainWindow::slotRadioButtonChecked()
{
    QRadioButton *radioButton = qobject_cast<QRadioButton*> (sender());

    if(radioButton->objectName() == QString("autoConnectionRadioButton"))
    {
        connectionType = Qt::AutoConnection;
        ui->descriptionEextEdit->setText("(default) If the signal is emitted from a different thread than the receiving object, the signal is queued, behaving as Qt::QueuedConnection. Otherwise, the slot is invoked directly, behaving as Qt::DirectConnection. The type of connection is determined when the signal is emitted.");
    }
    else if(radioButton->objectName() == QString("queuedConnectionRadioButton"))
    {
        connectionType = Qt::QueuedConnection;
        ui->descriptionEextEdit->setText("The slot is invoked when control returns to the event loop of the receiver's thread. The slot is executed in the receiver's thread.");

    }
    else if(radioButton->objectName() == QString("blockingQueuedConnectionRadioButton"))
    {
        connectionType = Qt::BlockingQueuedConnection;
        ui->descriptionEextEdit->setText("Same as QueuedConnection, except the current thread blocks until the slot returns. This connection type should only be used where the emitter and receiver are in different threads. Note: Violating this rule can cause your application to deadlock.");
    }

    reconnectCars();
}

void MainWindow::slotReceiver(const QString &str, int value)
{
    ui->resultTextEdit->insertPlainText(str + " cycle " + QString::number(value) + "\n");
}

void MainWindow::setConnections()
{
    connect(ui->runButton, SIGNAL(clicked()), this, SLOT(slotRun()));
    connect(ui->autoConnectionRadioButton, SIGNAL(clicked()), this, SLOT(slotRadioButtonChecked()));
    connect(ui->queuedConnectionRadioButton, SIGNAL(clicked()), this, SLOT(slotRadioButtonChecked()));
    connect(ui->blockingQueuedConnectionRadioButton, SIGNAL(clicked()), this, SLOT(slotRadioButtonChecked()));
    connect(mercedes.data(), SIGNAL(signalFromCar(const QString&, int)), this, SLOT(slotReceiver(const QString&, int)), connectionType);
    connect(ferrari.data(), SIGNAL(signalFromCar(const QString&, int)), this, SLOT(slotReceiver(const QString&, int)), connectionType);
}

void MainWindow::reconnectCars()
{
    disconnect(mercedes.data(), SIGNAL(signalFromCar(const QString&, int)), this, SLOT(slotReceiver(const QString&, int)));
    disconnect(ferrari.data(), SIGNAL(signalFromCar(const QString&, int)), this, SLOT(slotReceiver(const QString&, int)));
    connect(mercedes.data(), SIGNAL(signalFromCar(const QString&, int)), this, SLOT(slotReceiver(const QString&, int)), connectionType);
    connect(ferrari.data(), SIGNAL(signalFromCar(const QString&, int)), this, SLOT(slotReceiver(const QString&, int)), connectionType);
}
