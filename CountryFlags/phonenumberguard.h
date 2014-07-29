/*
   Copyright (C) Oleg Ziakun
*/

#ifndef PHONENUMBERGUARD_H
#define PHONENUMBERGUARD_H

#include <QLineEdit>

/* This class provides  utilities for phone number checking and service */

class PhoneNumberGuard
{
public:
    PhoneNumberGuard(QLineEdit *le);

public:
    bool isInputAllowed(const QString &text);
    bool isPasteAllowed(const QString &text);
    void clearInput();

protected:
    QLineEdit *lineEdit;
    const QString prefixSign;
    const QString enterText;
};

#endif // PHONENUMBERGUARD_H
