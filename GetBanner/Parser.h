/*
   Copyright (C) Oleg Ziakun
*/

#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QStringList>

class Parser
{
public:

    enum EExpression
    {
        ELeft = 0,
        ERight
    };

    Parser(QString str, const QString sep = ";");
    ~Parser();

public:
    QString GetResponseValue(int response) const;
    QString GetKeyValue(const QString& strVal, const QString& sep = "=") const;
    void DecodeWebStr(QString& str, const QString& sep = "=");
    bool IsCompleteDataReceived(void);

private:
    void GetValues(void);

private:
    QString strToParse;
    QStringList strValues;
    QString separator;
};

#endif // PARSER_H
