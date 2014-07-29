/*
   Copyright (C) Oleg Ziakun
*/

#include "paser.h"
#include <QFile>
#include <QStringList>

CSVParser::CSVParser()
{  
}

void CSVParser::init(const QString &res)
{
    QFile file(res);

    file.open(QIODevice::ReadOnly);
    content = file.readAll();

    parse();

    file.close();
}

QMap<QString, CSVParser::CountryData> CSVParser::getCountryData() const
{
    return countryData;
}

/* pares CVS file */

void CSVParser::parse()
{
    QStringList tokenValues(content.split("\n"));

    foreach(QString token, tokenValues)
    {
        QStringList values(token.split(","));

        for(int i = 0; i < values.count(); ++i)
            values[i] = values[i].simplified();

        CountryData currentCountryData;

        currentCountryData.phonePrefix = values[EPhonePrefix];
        currentCountryData.name = values[EName];
        currentCountryData.code = values[ECode];

        countryData[values[ENumber]] = currentCountryData;
    }
}

void PhoneNumberParser::init(const QMap<QString, Parser::CountryData> &data)
{
    countryData = data;
}

/* gets phone prefix (i.e. Id) */

QString PhoneNumberParser::getPhonePrefix(const QString &countryNumber) const
{
    return countryData[countryNumber].phonePrefix;
}

/* gets country number (i.e. Id) */

QString PhoneNumberParser::getCountryNumber(const QString &text) const
{
    int minPhonePrefixLength = 1;
    int maxPhonePrefixLength = 4;

    if(text.length() < minPhonePrefixLength) return QString();

    QStringList keys(countryData.keys());
    QString countryNumber;
    QString analyzingText;

    foreach(QString phonePrefixId , keys)
    {
        for(int i = maxPhonePrefixLength; i >= minPhonePrefixLength; --i)
        {
            analyzingText = text.mid(minPhonePrefixLength - 1, i);

            if(countryData[phonePrefixId].phonePrefix == analyzingText)
            {
                countryNumber = phonePrefixId;
                break;
            }
        }
    }

    return countryNumber;
}


