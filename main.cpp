#include<iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <strategysort.h>

int main(int argc, char *argv[])
{
       int a = SortsEnums::SortChoice::QUICK_SORT ;
       std::cout<<a<<std::endl;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Core_Direction");
    QCoreApplication::setApplicationName("SortVisualizer");
    qmlRegisterUncreatableType<SortsEnums>("SortVisualizer",1,0,"SortChoice",
        QStringLiteral("This object should not be created in qml"));

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);




    return app.exec();
}
