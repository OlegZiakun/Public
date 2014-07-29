/*
   Copyright (C) Oleg Ziakun
*/

#ifndef CAR_H
#define CAR_H

#include <QThread>

class Car : public QThread
{
    Q_OBJECT
public:
    explicit Car(const QString &n, QObject *parent = 0);
        
signals:
    void signalFromCar(const QString&, int);

public:
    void run();

protected:
    const int count = 10;
    QString name;
};

#endif // CAR_H
