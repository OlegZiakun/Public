/*
   Copyright (C) Oleg Ziakun
*/

#include "styles.h"

Styles::Styles()
{
}

QString Styles::getStyleSheet(const QString &code) const
{
    return QString("QLineEdit#phoneNumberEdit{border-image: url(:/background/resources/field_normal.png);image: url(:/background/resources/countries/flags/" +
                   code +
                   ".jpg);image-position: left; border-left-width: 10px;}");
}
