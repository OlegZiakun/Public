/*
   Copyright (C) Oleg Ziakun
*/

#ifndef ITEMLOADER_H
#define ITEMLOADER_H

#include <QObject>
#include <QLineEdit>
#include "contextmenu.h"
#include "phonenumberguard.h"
#include "paser.h"

/* This class provides items loading */

class ItemLoader : public QObject, public PhoneNumberGuard
{
    Q_OBJECT
public:
    explicit ItemLoader(const QString &infoFile, QLineEdit *le, QObject *parent = 0);

public:
    bool eventFilter(QObject *object, QEvent *event);

public:
    void load(const QString &loadFrom);
    void showContextMenu();
    QString getCountryCode(const QString& text) const;
    bool checkInput(const QString &text);
    bool checkPaste(const QString &text);

private slots:
    void setCountryInfoFromMenu(const QString& code);

private:
    QLineEdit *lineEdit;
    QScopedPointer<ContextMenu> contextMenu;
    QScopedPointer<CSVParser> csvParser;
    QScopedPointer<PhoneNumberParser> phoneNumberPaser;
};

#endif // ITEMLOADER_H
