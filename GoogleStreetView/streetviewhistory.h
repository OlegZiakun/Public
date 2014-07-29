/*
   Copyright (C) Oleg Ziakun
*/

#ifndef STREETVIEWHISTORY_H
#define STREETVIEWHISTORY_H

#include <QObject>
#include <QSettings>
#include "ui_mainwindow.h"

class StreetViewHistory : public QObject
{
    Q_OBJECT
public:
    explicit StreetViewHistory(Ui::MainWindow *mw, QObject *parent = 0);

public:
    void load();
    void add(const QString &as);
    bool inUse() const;
    void markItem(int index);
    void reset(bool inUseFlag = true);

signals:
    void historyItemClicked(const QString &itemText);

private slots:
    void historyItemClicked(QTableWidgetItem *item);
    void removeButtonClicked();
    void removeAllButtonClicked();

private:
    void init();
    void clear();
    void setTabView();
    void setItems();
    void setConnections();
 void setUseFlag(bool inUseFlag);

private:
    Ui::MainWindow *mainWindow;
    QScopedPointer<QSettings> settings;
    QString idsCountValueString;
    QString idNumberString;
    int itemsCount;
};

#endif // STREETVIEWHISTORY_H
