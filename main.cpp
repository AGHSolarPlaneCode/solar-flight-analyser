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


    // example of error types
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Urgent Error";
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Information";
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Inherit Error";
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Access denied";
    RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Warning";


    ErrorSingleton::showErrorsQueue();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("errorManager", ErrorSingleton::getInstance());

    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();

}
