#include <QApplication>
#include <QQmlApplicationEngine>
#include "flightdatacontroller.h"
#include "weatherapi.h"
#include <QtQuick>
#include <QPointer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);


//    qRegisterMetaType<FlightData>("FlightData");

    QPointer<FlightDataController> controller(new FlightDataController());
 //   std::unique_ptr<FlightDataController> controller(new FlightDataController());
//    WeatherAPI *weather = new WeatherAPI(); //instance of weatherAPI - for test



//    engine.rootContext()->setContextProperty("controller",controller);
//    engine.rootContext()->setContextProperty("adapter", controller->getAdapter());
//    engine.rootContext()->setContextProperty("error", controller->getError());
//    engine.rootContext()->setContextProperty("weatherAPIAdapter", weather); //context for QPROPERTY

//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;


    if(!controller->initializeQMLObjects())
        return -1;


    return app.exec();

}
