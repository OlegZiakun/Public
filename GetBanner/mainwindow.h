/*
   Copyright (C) Oleg Ziakun
*/

/********************************************************************
* Description: eBuddy Mobile Assignment                            ----
*                                                                  ----
* Author: Oleg Ziakun                                              ----
* email: symbiantop@gmail.com                                      ----
*********************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ConnectionManager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_connectButton_clicked();
    void slotDisplayText(QString str);
    void slotDisplayImage(QString data);

private:
    void StopSpinner(void);

private:
    ConnectionManager* connMgr;
    QMovie *movie;
};

#endif // MAINWINDOW_H
