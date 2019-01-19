#-------------------------------------------------
#
# Project created by QtCreator 2017-11-24T18:26:24
#
#-------------------------------------------------

QT     += core gui
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageRecognizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    contouranalysis.cpp

HEADERS  += mainwindow.h \
    contouranalysis.h

FORMS    += mainwindow.ui


INCLUDEPATH += $$PWD/../../../opencv/include
DEPENDPATH += $$PWD/../../../opencv/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencvBuild/lib/release/ -lopencv_highgui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencvBuild/lib/debug/ -lopencv_highgui
else:unix: LIBS += -L$$PWD/../../../opencvBuild/lib/ -lopencv_highgui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencvBuild/lib/release/ -lopencv_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencvBuild/lib/debug/ -lopencv_core
else:unix: LIBS += -L$$PWD/../../../opencvBuild/lib/ -lopencv_core

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencvBuild/lib/release/ -lopencv_imgproc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencvBuild/lib/debug/ -lopencv_imgproc
else:unix: LIBS += -L$$PWD/../../../opencvBuild/lib/ -lopencv_imgproc
