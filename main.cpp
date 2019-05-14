#include <QApplication>
#include <QQmlApplicationEngine>
#include "flightdatacontroller.h"
#include "weatherapi.h"
#include <QtQuick>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    qRegisterMetaType<FlightData>("FlightData");
    FlightDataController *controller = new FlightDataController();


    WeatherAPI *weather = new WeatherAPI(); //instance of weatherAPI - for test
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("controller",controller);
    engine.rootContext()->setContextProperty("adapter", controller->getAdapter());
    engine.rootContext()->setContextProperty("error", controller->getError());
    engine.rootContext()->setContextProperty("weatherAPIAdapter", weather); //context for QPROPERTY

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();

}
