/*
   Copyright (C) Oleg Ziakun
*/

#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QMap>
#include <QString>
#include "qt_windows.h"

class SystemInfo
{
public:
    SystemInfo();
    ~SystemInfo();

public:
    QString getOSInfo(QSysInfo::WinVersion ver) const;
    MEMORYSTATUSEX getMemoryStatusEx() const;
    void getMemoryStatus();

private:
    void FillOSInfo();

private:
    MEMORYSTATUSEX memoryStatus;
    QMap<QSysInfo::WinVersion, QString> strListOS;
};

#endif // SYSTEMINFO_H
