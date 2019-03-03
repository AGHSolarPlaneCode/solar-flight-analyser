#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "flightdatacontroller.h"
#include <QtQuick>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qRegisterMetaType<FlightData>("FlightData");
    FlightDataController *controller = new FlightDataController();



    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("controller",controller);
    engine.rootContext()->setContextProperty("adapter", controller->getAdapter());
    engine.rootContext()->setContextProperty("error", controller->getError());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();

}
