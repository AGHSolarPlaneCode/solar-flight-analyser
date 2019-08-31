#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include "weatherapi.h"
#include "datamanager.h"
#include "errorsingleton.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);  
    QQmlApplicationEngine engine;
    DataManager manager;
    WeatherAPI weather;

    // example of error types
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Urgent Error";
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Information";
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Inherit Error";
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Access denied";
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Warning";


    ErrorSingleton::showErrorsQueue();
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("errorManager", ErrorSingleton::getInstance());
    engine.rootContext()->setContextProperty("adapter",&manager);
    engine.rootContext()->setContextProperty("weather", &weather);    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
