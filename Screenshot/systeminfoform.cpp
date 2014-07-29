/*
   Copyright (C) Oleg Ziakun
*/

#include "systeminfoform.h"
#include "ui_systeminfoform.h"

SystemInfoForm::SystemInfoForm(SystemInfo& si, QWidget *parent) :  
    QDialog(parent),
    ui(new Ui::SystemInfoForm),
    systemInfo(si)
{
    ui->setupUi(this);
    displaySystemInfo();
}

SystemInfoForm::~SystemInfoForm()
{
    delete ui;
}

void SystemInfoForm::on_okButton_clicked()
{
    close();
}

void SystemInfoForm::displaySystemInfo(void)
{
     const int coefficient = 1024 * 1024;

    ui->labelOSText->setText(systemInfo.getOSInfo(QSysInfo::windowsVersion()));
    systemInfo.getMemoryStatus(); ui->labelMemoryLoadText->setText(QString::number(systemInfo.getMemoryStatusEx().dwMemoryLoad) + "%");
    systemInfo.getMemoryStatus(); ui->labelTotalMemoryText->setText(QString::number(systemInfo.getMemoryStatusEx().ullTotalPhys / coefficient)+ " MB");
    systemInfo.getMemoryStatus(); ui->labelAvailMemoryText->setText(QString::number(systemInfo.getMemoryStatusEx().ullAvailPhys / coefficient)+ " MB");
    systemInfo.getMemoryStatus(); ui->labelTotalPageFileText->setText(QString::number(systemInfo.getMemoryStatusEx().ullTotalPageFile / coefficient)+ " MB");
    systemInfo.getMemoryStatus(); ui->labelAvailPageFileText->setText(QString::number(systemInfo.getMemoryStatusEx().ullAvailPageFile / coefficient)+ " MB");
    systemInfo.getMemoryStatus(); ui->labelTotalVirtualMemoryText->setText(QString::number(systemInfo.getMemoryStatusEx().ullTotalVirtual / coefficient)+ " MB");
    systemInfo.getMemoryStatus(); ui->labelAvailVirtualMemoryText->setText(QString::number(systemInfo.getMemoryStatusEx().ullAvailVirtual / coefficient)+ " MB");
}
