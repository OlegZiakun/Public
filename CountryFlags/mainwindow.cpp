/*
   Copyright (C) Oleg Ziakun
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "styles.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    maxLength(160),
    inputText(tr("Type message"))
{
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    ui->setupUi(this);

    ui->smsTextEdit->setText(inputText);

    itemloader.reset(new ItemLoader(":/info/resources/countries/countries.txt", ui->phoneNumberEdit));
    itemloader->load(":/background/resources/countries/flags/");

    connect(ui->dropDownButton, SIGNAL(clicked()), this, SLOT(clickedMenu()));
    connect(ui->phoneNumberEdit, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
    connect(ui->smsTextEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
    connect(ui->smsTextEdit, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(clickedButton()));
}

void MainWindow::clickedMenu()
{
    itemloader->showContextMenu();
}

/* textChanged event for phone number editor  */

void MainWindow::textChanged(const QString& text)
{      
    if(!itemloader->checkInput(text)) return;

    if(!itemloader->checkPaste(text))
    {
        msg(tr("Wrong input. Please check your phone number."));
        return;
    }

    QString code(itemloader->getCountryCode(text));

    if(!code.isEmpty())
    {
        ui->phoneNumberEdit->setStyleSheet(Styles().getStyleSheet(code));
    }
}

/* textChanged event for SMS editor  */

void MainWindow::textChanged()
{
    QString text(ui->smsTextEdit->toPlainText());
    int textLength = text.length();

    ui->countLabel->setText(QString::number(textLength) + "/1"); 

    if(textLength > maxLength)
    {
        text.truncate(maxLength);

        if(fullText.length() < maxLength)
            ui->smsTextEdit->setText(text);
        else
            ui->smsTextEdit->setText(fullText);

        setCursorToTheEnd();
    }

    fullText = ui->smsTextEdit->toPlainText();
}

void MainWindow::cursorPositionChanged()
{
    static bool allow = true;

    if(ui->smsTextEdit->toPlainText() == inputText && allow)
    {
        allow = false;

        ui->smsTextEdit->clear();
        ui->smsTextEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
    }
}

void MainWindow::setCursorToTheEnd()
{
    QTextCursor cursor(ui->smsTextEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    ui->smsTextEdit->setTextCursor(cursor);
}

void MainWindow::clickedButton()
{
    msg("Hello I'm the send button. I can send whatever you would like.");
}

void MainWindow::msg(const QString& text)
{
    QMessageBox msgBox;

    msgBox.setText(text);
    msgBox.exec();
}
