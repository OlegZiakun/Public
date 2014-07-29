/*
   Copyright (C) Oleg Ziakun
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mercedes.h"
#include "ferrari.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotRun();
    void slotReceiver(const QString &str, int value);
    void slotRadioButtonChecked();
    void setConnections();
    void reconnectCars();

private:
    void init();

private:
    Qt::ConnectionType connectionType = Qt::AutoConnection;
    QScopedPointer<Mercedes> mercedes;
    QScopedPointer<Ferrari> ferrari;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
