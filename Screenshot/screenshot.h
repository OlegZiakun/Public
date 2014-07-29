/*
   Copyright (C) Oleg Ziakun
*/

#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QPixmap>
#include <QWidget>
#include "systeminfo.h"
#include "systeminfoform.h"
#include "sendinfo.h"
#include "screenshot.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGridLayout;
class QGroupBox;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QSpinBox;
class QVBoxLayout;
QT_END_NAMESPACE

class SystemInfo;

class Screenshot : public QWidget
{
    Q_OBJECT

public:
    Screenshot();
    ~Screenshot();

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    void signalSendInfo(QByteArray imageData);

public slots:
    void slotNewScreenshot();
    void slotSendInfo();
    void slotShootScreen();
    void slotUpdateCheckBox();
    void slotSystemInfo();
    void slotUploadFinished();

private:
    void createOptionsGroupBox();
    void createButtonsLayout();
    QPushButton *createButton(const QString &text, QWidget *receiver, const char *member);
    void updateScreenshotLabel();

    QPixmap originalPixmap;

    QLabel *screenshotLabel;
    QGroupBox *optionsGroupBox;
    QSpinBox *delaySpinBox;
    QLabel *delaySpinBoxLabel;
    QCheckBox *hideThisWindowCheckBox;
    QPushButton *newScreenshotButton;
    QPushButton *systemInfoButton;
    QPushButton *sendInfoButton;
    QPushButton *quitScreenshotButton;

    QVBoxLayout *mainLayout;
    QGridLayout *optionsGroupBoxLayout;
    QHBoxLayout *buttonsLayout;

    SystemInfo* systemInfo;
    SystemInfoForm* systemInfoForm;
    SendInfo* sendInfo;
};

#endif
