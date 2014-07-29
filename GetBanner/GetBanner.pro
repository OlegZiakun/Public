#-------------------------------------------------
#
# Project created by QtCreator 2012-01-19T21:11:48
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = GetBanner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ConnectionManager.cpp \
    Parser.cpp

HEADERS  += mainwindow.h \
    ConnectionManager.h \
    Parser.h \
    Def.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xe788f77a
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
