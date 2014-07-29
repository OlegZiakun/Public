/*
   Copyright (C) Oleg Ziakun
*/

#include "systeminfo.h"

SystemInfo::SystemInfo()
{
    FillOSInfo();
}

SystemInfo::~SystemInfo()
{
}

void SystemInfo::FillOSInfo()
{
    strListOS[QSysInfo::WV_32s] = "Windows 3.1 with Win 32s";
    strListOS[QSysInfo::WV_95] = "Windows 95";
    strListOS[QSysInfo::WV_98] = "Windows 98";
    strListOS[QSysInfo::WV_Me] = "Windows Me";
    strListOS[QSysInfo::WV_NT] = "Windows NT (operating system version 4.0)";
    strListOS[QSysInfo::WV_2000] = "Windows 2000 (operating system version 5.0)";
    strListOS[QSysInfo::WV_XP] = "Windows XP (operating system version 5.1)";
    strListOS[QSysInfo::WV_2003] = "(operating system version 5.2)";
    strListOS[QSysInfo::WV_VISTA] = "Windows Vista (operating system version 6.0)";
    strListOS[QSysInfo::WV_WINDOWS7] = "Windows 7  (operating system version 6.1)";
}

QString SystemInfo::getOSInfo(QSysInfo::WinVersion ver) const
{
    QString verStr("undefined");

    if(strListOS.contains(ver))
        verStr = strListOS.find(ver).value();

    return verStr;
}

void SystemInfo::getMemoryStatus()
{
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);
}

MEMORYSTATUSEX SystemInfo::getMemoryStatusEx() const
{
    return memoryStatus;
}
