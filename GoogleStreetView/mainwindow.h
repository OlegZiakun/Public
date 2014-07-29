/*
   Copyright (C) Oleg Ziakun
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "streetviewmanager.h"

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
    void init();
    void setConnections();

private:
    Ui::MainWindow *ui;
    QScopedPointer<StreetViewManager> streetViewManager;
};

#endif // MAINWINDOW_H
