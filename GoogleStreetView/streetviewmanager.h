/*
   Copyright (C) Oleg Ziakun
*/

#ifndef STREETVIEWMANAGER_H
#define STREETVIEWMANAGER_H

#include <QObject>
#include <QString>
#include "streetviewhistory.h"
#include "ui_mainwindow.h"

class StreetViewManager : public QObject
{
    Q_OBJECT
public:
    explicit StreetViewManager(Ui::MainWindow *mw, QObject *parent = 0);

private slots:
    void viewButtonClicked();
    void slidersReleased();
    void historyItemClicked(const QString &itemText);
    void defaultButtonClicked();

private:
    void init();
    void setLocation();
    void setConnections();
    void reset();
    void setExampleLocations();
    void addDefault();

private:
    Ui::MainWindow *mainWindow;
    QScopedPointer<StreetViewHistory> streetViewHistory;
    QString mainUrl;
    QString location;
    int heading;
    int fov;
    int pitch;
};

#endif // STREETVIEWMANAGER_H
