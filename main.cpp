#include<iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "strategysort.h"
#include "strategysortnavigation.h"

int main(int argc, char *argv[])
{
    srand((int)time(0));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Core_Direction");
    QCoreApplication::setApplicationName("SortVisualizer");
    qmlRegisterUncreatableType<SortsEnums>("SortVisualizer",1,0,"Sortchoice",
        QStringLiteral("This object should not be created in qml"));
    qRegisterMetaType<SortsEnums::SortChoice>("SortEnums::SortChoice");

    StrategySortNavigation navigationClass;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("navigationClass"), &navigationClass);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);




    return app.exec();
}
