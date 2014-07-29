#-------------------------------------------------
#
# Project created by QtCreator 2013-06-03T09:20:28
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoogleStreetView
TEMPLATE = app

SOURCES += main.cpp
SOURCES += streetviewmanager.cpp
SOURCES += streetviewhistory.cpp
SOURCES += mainwindow.cpp

HEADERS += mainwindow.h
HEADERS += streetviewmanager.h
HEADERS += streetviewhistory.h

FORMS    += mainwindow.ui

RESOURCES += res.qrc

