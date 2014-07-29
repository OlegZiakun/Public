/*
   Copyright (C) Oleg Ziakun
*/

#ifndef STYLES_H
#define STYLES_H

#include <QString>

/* Class for working  with stylesheets */

class Styles
{
public:
    Styles();

public:
    QString getStyleSheet(const QString &code) const;
};

#endif // STYLES_H
