#-------------------------------------------------
#
# Project created by QtCreator 2013-11-17T17:21:12
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Connections
TEMPLATE = app

SOURCES += main.cpp \
    car.cpp
SOURCES += mainwindow.cpp
SOURCES += mercedes.cpp
SOURCES += ferrari.cpp

HEADERS  += mainwindow.h \
    car.h
HEADERS  += mercedes.h
HEADERS  += ferrari.h

FORMS    += mainwindow.ui
