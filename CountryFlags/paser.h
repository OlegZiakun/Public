/*
   Copyright (C) Oleg Ziakun
*/

#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QMap>

/* Base class for parsing */

class Parser
{
public:
    Parser(){}
    virtual ~Parser(){}

    enum ECountryData
    {
        ENumber,
        EPhonePrefix,
        EName,
        ECode
    };

    struct CountryData
    {
        QString name;
        QString phonePrefix;
        QString code;
    };

protected:
    QString content;
    QMap<QString, CountryData> countryData;
};





/* Class for CVS file parsing */

class CSVParser: public Parser
{
public:   
    CSVParser();

public:
    void init(const QString &res);
    void parse();

public:
    QMap<QString, CountryData> getCountryData() const;
};




/* Class for phone number file parsing */

class PhoneNumberParser: public Parser
{
public:
    PhoneNumberParser(){}

public:
    void init(const QMap<QString, CountryData> &data);
    void parse();

public:
    QString getPhonePrefix(const QString &countryNumber) const;
    QString getCountryNumber(const QString &text) const;

private:
    QString phonePrefix;
};

#endif // PARSER_H
