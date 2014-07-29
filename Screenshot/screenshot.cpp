/*
   Copyright (C) Oleg Ziakun
*/

#include <QtGui>
#include <QMessageBox>
#include "screenshot.h"
#include "sendinfo.h"

Screenshot::Screenshot():
    systemInfo(NULL),
    systemInfoForm(NULL),
    sendInfo(NULL)
{
    screenshotLabel = new QLabel;

    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    screenshotLabel->setAlignment(Qt::AlignCenter);
    screenshotLabel->setMinimumSize(400, 300);

    createOptionsGroupBox();
    createButtonsLayout();

    mainLayout = new QVBoxLayout;

    mainLayout->addWidget(screenshotLabel);
    mainLayout->addWidget(optionsGroupBox);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    slotShootScreen();
    delaySpinBox->setValue(1);

    setWindowTitle(tr("Screenshot"));
    resize(300, 200);

    if(!systemInfo)
        systemInfo = new SystemInfo;
}

Screenshot::~Screenshot()
{
    if(systemInfo)
        delete systemInfo;

    if(systemInfoForm)
        delete systemInfoForm;
}

void Screenshot::resizeEvent(QResizeEvent * /* event */)
{
    QSize scaledSize = originalPixmap.size();

    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);

    if(!screenshotLabel->pixmap() || scaledSize != screenshotLabel->pixmap()->size())
        updateScreenshotLabel();
}

void Screenshot::slotNewScreenshot()
{
    if(hideThisWindowCheckBox->isChecked())
        hide();

    newScreenshotButton->setDisabled(true);

    QTimer::singleShot(delaySpinBox->value() * 1000, this, SLOT(slotShootScreen()));
}

void Screenshot::slotSendInfo()
{
    QString format = "png";
    QByteArray data;
    QBuffer buffer(&data);

    sendInfoButton->setEnabled(false);

    buffer.open(QIODevice::WriteOnly);

    if(!originalPixmap.save(&buffer, format.toAscii()))
    {
        QMessageBox msgBox;
        msgBox.setText("Error occured while converting screenshot image. OS configuration data will be send only");
        msgBox.exec();
    }

    if(!sendInfo)
        sendInfo = new SendInfo(*systemInfo,this);

    connect(sendInfo, SIGNAL(UploadFinished()),this, SLOT(slotUploadFinished()));

    emit signalSendInfo(data);
}

void Screenshot::slotShootScreen()
{
    if (delaySpinBox->value() != 0)
        qApp->beep();

    originalPixmap = QPixmap();
    originalPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());

    updateScreenshotLabel();

    newScreenshotButton->setDisabled(false);

    if (hideThisWindowCheckBox->isChecked())
        show();
}

void Screenshot::slotUpdateCheckBox()
{
    if (delaySpinBox->value() == 0)
    {
        hideThisWindowCheckBox->setDisabled(true);
        hideThisWindowCheckBox->setChecked(false);
    }
    else
        hideThisWindowCheckBox->setDisabled(false);
}

void Screenshot::createOptionsGroupBox()
{
    optionsGroupBox = new QGroupBox(tr("Options"));

    delaySpinBox = new QSpinBox;
    delaySpinBox->setSuffix(tr(" s"));
    delaySpinBox->setMaximum(60);

    connect(delaySpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateCheckBox()));

    delaySpinBoxLabel = new QLabel(tr("Screenshot Delay:"));

    hideThisWindowCheckBox = new QCheckBox(tr("Hide This Window"));

    optionsGroupBoxLayout = new QGridLayout;
    optionsGroupBoxLayout->addWidget(delaySpinBoxLabel, 0, 0);
    optionsGroupBoxLayout->addWidget(delaySpinBox, 0, 1);
    optionsGroupBoxLayout->addWidget(hideThisWindowCheckBox, 1, 0, 1, 2);
    optionsGroupBox->setLayout(optionsGroupBoxLayout);
}

void Screenshot::createButtonsLayout()
{
    newScreenshotButton = createButton(tr("New Screenshot"),this, SLOT(slotNewScreenshot()));
    systemInfoButton = createButton(tr("System Info"), this, SLOT(slotSystemInfo()));
    sendInfoButton = createButton(tr("Send Info"),this, SLOT(slotSendInfo()));
    quitScreenshotButton = createButton(tr("Quit"), this, SLOT(close()));

    newScreenshotButton->setCursor(Qt::PointingHandCursor);
    systemInfoButton->setCursor(Qt::PointingHandCursor);
    sendInfoButton->setCursor(Qt::PointingHandCursor);
    quitScreenshotButton->setCursor(Qt::PointingHandCursor);

    buttonsLayout = new QHBoxLayout;

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(newScreenshotButton);
    buttonsLayout->addWidget(systemInfoButton);
    buttonsLayout->addWidget(sendInfoButton);
    buttonsLayout->addWidget(quitScreenshotButton);
}

QPushButton *Screenshot::createButton(const QString &text, QWidget *receiver, const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->connect(button, SIGNAL(clicked()), receiver, member);
    return button;
}

void Screenshot::updateScreenshotLabel()
{
    screenshotLabel->setPixmap(originalPixmap.scaled(screenshotLabel->size() ,Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Screenshot::slotSystemInfo()
{
    systemInfoForm = new SystemInfoForm(*systemInfo);
    systemInfoForm->show();
}

void Screenshot::slotUploadFinished()
{
  sendInfoButton->setEnabled(true);
}
