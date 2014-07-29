/*
   Copyright (C) Oleg Ziakun
*/

#ifndef MERCEDES_H
#define MERCEDES_H

#include "car.h"

class Mercedes : public Car
{
    Q_OBJECT
public:
    Mercedes(QObject *parent = NULL);
};

#endif // MERCEDES_H
