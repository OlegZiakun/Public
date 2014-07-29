/*
   Copyright (C) Oleg Ziakun
*/

#include "car.h"

Car::Car( const QString &n,QObject *parent) :
    QThread(parent),
    name(n)
{
}

void Car::run()
{
    for(int i = 0; i < count; ++i)
        signalFromCar(name, i);
}
