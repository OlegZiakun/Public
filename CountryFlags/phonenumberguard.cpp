/*
   Copyright (C) Oleg Ziakun
*/

#include "phonenumberguard.h"
#include "styles.h"
#include <QFont>
#include <QObject>

PhoneNumberGuard::PhoneNumberGuard(QLineEdit *le) :
    lineEdit(le),
    prefixSign("+"),
    enterText(QObject::tr("enter phone number"))
{    
}

/* cheks for wrong/right input */

bool PhoneNumberGuard::isInputAllowed(const QString &text)
{
    if(text.isEmpty())
    {
        lineEdit->setStyleSheet(Styles().getStyleSheet(QString()));
        return false;
    }

    QChar currentChar(text[text.length() - 1]);
    QString currentText(text);

    if(!text[0].isNumber() && QString(text[0]) != prefixSign)
    {
        currentText.truncate(0);
        lineEdit->setText(QString());
        return false;
    }

    if(text.length() > 1)
    {
        if(!currentChar.isNumber())
        {
            currentText.truncate(text.length() - 1);
            lineEdit->setText(currentText);
            return false;
        }
    }

    return true;
}

/* cheks for wrong/right paste from an external application */

bool PhoneNumberGuard::isPasteAllowed(const QString &text)
{
    bool is = true;

    if(text[0].isNumber() || QString(text[0]) == prefixSign)
    {
        for(int i = 1; i < text.length(); ++i)
        {
            if(!text[i].isNumber())
            {
                is = false;
                break;
            }
        }
    }
    else
    {
        is = false;
    }

    return is;
}

void PhoneNumberGuard::clearInput()
{
    lineEdit->clear();
    lineEdit->setFont(QFont());
}
