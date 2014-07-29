/*
   Copyright (C) Oleg Ziakun
*/

#include "Parser.h"
#include "Def.h"

Parser::Parser(QString str, const QString sep) : strToParse(str), separator(sep)
{
    GetValues();
}

Parser::~Parser()
{
}

QString Parser::GetResponseValue(int response) const
{
    return strValues[response];
}

void Parser::GetValues(void)
{
    strValues = strToParse.split(separator);
}

QString Parser::GetKeyValue(const QString& strVal, const QString& sep) const
{
    QString str = NULL;

    for(int i = 0; i < strValues.count(); i++)
    {
        QStringList strList = strValues[i].split(sep);

        if (strList[ELeft] == strVal)
        {
            str = strList[ERight];
            break;
        }
    }

    return str;
}

void Parser::DecodeWebStr(QString& str, const QString& sep)
{
    for(int i = 0; i < strValues.count(); i++)
    {
        QStringList strList = strValues[i].split(sep);
        str.replace(strList[ELeft],strList[ERight]);
    }
}

bool Parser::IsCompleteDataReceived(void)
{
 bool res = false;
 QString lastStrReceived(GetResponseValue(strValues.count() - 1));

 if(lastStrReceived[lastStrReceived.count() - 1] == END_TOKEN)
    res = true;

 return res;
}
