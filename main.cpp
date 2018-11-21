#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "routeplanner.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    RoutePlanner simulationRoute;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("simulationRoute",&simulationRoute);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
