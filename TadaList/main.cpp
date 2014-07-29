/*
   Copyright (C) Oleg Ziakun
*/

#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "tadalistengine.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QDeclarativeView view;
    TadaListEngine tdlEngine(view);

    view.rootContext()->setContextProperty("tdlObject", &tdlEngine);
    tdlEngine.loadView("qml/TadaList/main.qml");

    return app.exec();
}
