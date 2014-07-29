QT       += network

HEADERS             = screenshot.h \
    systeminfo.h \
    systeminfoform.h \
    sendinfo.h
SOURCES             = main.cpp \
                      screenshot.cpp \
    systeminfo.cpp \
    systeminfoform.cpp \
    sendinfo.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/desktop/screenshot
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS screenshot.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/desktop/screenshot
INSTALLS += target sources

symbian: include($$PWD/../../symbianpkgrules.pri)
maemo5: include($$PWD/../../maemo5pkgrules.pri)
contains(MEEGO_EDITION,harmattan): include($$PWD/../../harmattanpkgrules.pri)
symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example might not fully work on Maemo platform)
contains(MEEGO_EDITION,harmattan): warning(This example might not fully work on Harmattan platform)
simulator: warning(This example might not fully work on Simulator platform)

FORMS += \
    systeminfoform.ui
