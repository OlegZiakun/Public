#-------------------------------------------------
#
# Project created by QtCreator 2013-02-05T19:06:32
#
#-------------------------------------------------

QT       += core gui

TARGET = CountryFlags
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    itemloader.cpp \
    contextmenu.cpp \
    paser.cpp \
    phonenumberguard.cpp \
    styles.cpp

HEADERS  += mainwindow.h \
    itemloader.h \
    contextmenu.h \
    paser.h \
    phonenumberguard.h \
    styles.h

FORMS    += mainwindow.ui \
    contextmenu.ui

RESOURCES += \
    res.qrc
