#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include "weatherapi.h"
#include "datamanager.h"
#include "errorsingleton.h"
#include "waypointservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);  
    QQmlApplicationEngine engine;
    app.setWindowIcon(QIcon(":/assetsMenu/icon.svg"));
    //QCoreApplication::setAttribute( Qt::AA_UseSoftwareOpenGL );
    std::shared_ptr<DataManager> dataWrapper = std::make_shared<DataManager>();

    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    WaypointService waypointService;

    engine.rootContext()->setContextProperty("errorManager", ErrorSingleton::getInstance());
    engine.rootContext()->setContextProperty("adapter", dataWrapper.get());
    engine.rootContext()->setContextProperty("waypoint", &waypointService);
//    engine.rootContext()->setContextProperty("weather", &weather);

    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
