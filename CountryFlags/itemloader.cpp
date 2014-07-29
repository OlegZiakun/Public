/*
   Copyright (C) Oleg Ziakun
*/

#include "itemloader.h"
#include "styles.h"
#include <QAction>
#include <QEvent>

ItemLoader::ItemLoader(const QString &infoFile, QLineEdit *le, QObject *parent) :
    QObject(parent),
    PhoneNumberGuard(le),
    lineEdit(le)
{
    contextMenu.reset(new ContextMenu());

    csvParser.reset(new CSVParser);
    phoneNumberPaser.reset(new PhoneNumberParser);

    csvParser->init(infoFile);
    lineEdit->setText(enterText);

    connect(contextMenu.data(), SIGNAL(currentCountryCode(const QString&)), this, SLOT(setCountryInfoFromMenu(const QString&)));
}

/* loads items here into context menu*/

void ItemLoader::load(const QString &loadFrom)
{
    QMap<QString, CSVParser::CountryData> countryData(csvParser->getCountryData());
    QString resPefix(loadFrom);
    QString imageExt(".jpg");
    const int fLength = 27;
    const int xTextMargin = 45;

    lineEdit->installEventFilter(this);

    phoneNumberPaser->init(countryData);

    lineEdit->setTextMargins(xTextMargin, 0, 0, 0);

    contextMenu->setFixedWidth(lineEdit->width());
    contextMenu->setCursor(Qt::PointingHandCursor);
    contextMenu->clear();

    for(int i = 1; i <= countryData.count(); ++i)
    {
        if(countryData.contains(QString::number(i)))
        {
            QString tab("\t");
            int jLength = fLength - countryData[QString::number(i)].name.length();

            tab = tab.rightJustified(jLength, ' ');

            QString text(countryData[QString::number(i)].name + (tab) + prefixSign + countryData[QString::number(i)].phonePrefix);
            QIcon icon(resPefix + QString::number(i) + imageExt);

            contextMenu->addItem(icon, text, QString::number(i));
        }
    }
}

void ItemLoader::showContextMenu()
{
    clearInput();

    contextMenu->move(lineEdit->mapToGlobal(QPoint(0,0)));
    contextMenu->show();
}

QString ItemLoader::getCountryCode(const QString &text) const
{
    QString optimizedText(text);

    if(QString(text[0]) == prefixSign)
        optimizedText.remove(prefixSign);

    return phoneNumberPaser->getCountryNumber(optimizedText);
}

/* sets country info into phone number editor from menu */

void ItemLoader::setCountryInfoFromMenu(const QString &code)
{
    lineEdit->setStyleSheet(Styles().getStyleSheet(code));
    lineEdit->setText(prefixSign + phoneNumberPaser->getPhonePrefix(code));
}

/* cheks for wrong/right input */

bool ItemLoader::checkInput(const QString &text)
{
    return isInputAllowed(text);
}

/* cheks for wrong/right paste from an external application */

bool ItemLoader::checkPaste(const QString &text)
{
    return isPasteAllowed(text);
}

/* when mouse clicked to enter text into phone number editor we need to clear the editor from inviting text */

bool ItemLoader::eventFilter(QObject *object, QEvent *event)
{
    if(object == lineEdit && event->type() == QEvent::MouseButtonPress)
        if(lineEdit->text() == enterText)
            clearInput();

    return QObject::eventFilter(object, event);
}
