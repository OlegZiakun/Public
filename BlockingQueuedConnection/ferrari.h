/*
   Copyright (C) Oleg Ziakun
*/

#ifndef FERRARI_H
#define FERRARI_H

#include "car.h"

class Ferrari : public Car
{
    Q_OBJECT
public:
    Ferrari(QObject *parent = NULL);
};

#endif // FERRARI_H
