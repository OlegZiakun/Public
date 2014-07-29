/*
   Copyright (C) Oleg Ziakun
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "itemloader.h"

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
    void msg(const QString &text);
    void setCursorToTheEnd();

private slots:
    void clickedMenu();
    void clickedButton();
    void textChanged(const QString &text);
    void textChanged();
    void cursorPositionChanged();

private:
    Ui::MainWindow *ui;
    QScopedPointer<ItemLoader> itemloader;
    const int maxLength;
    QString inputText;
    QString fullText;
};

#endif // MAINWINDOW_H
