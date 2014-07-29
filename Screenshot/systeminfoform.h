/*
   Copyright (C) Oleg Ziakun
*/

#ifndef SYSTEMINFOFORM_H
#define SYSTEMINFOFORM_H

#include <QDialog>
#include "systeminfo.h"

namespace Ui {
class SystemInfoForm;
}

class SystemInfoForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit SystemInfoForm(SystemInfo& si, QWidget *parent = 0);
    ~SystemInfoForm();

private:
    void displaySystemInfo(void);

private slots:
    void on_okButton_clicked();

private:
    Ui::SystemInfoForm *ui;
    SystemInfo& systemInfo;
};

#endif // SYSTEMINFOFORM_H
