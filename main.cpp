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
    RegisterError(WindowType::MainAppWindow, MessageType::WARINING) << "Urgent Error";
    RegisterError(WindowType::MainAppWindow, MessageType::WARINING) << "Information";
    RegisterError(WindowType::MainAppWindow, MessageType::WARINING) << "Inherit Error";
    RegisterError(WindowType::MainAppWindow, MessageType::WARINING) << "Access denied";
    RegisterError(WindowType::MainAppWindow, MessageType::WARINING) << "Warning";


    ErrorSingleton::showErrorsQueue();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    ///engine.rootContext()->setContextProperty("errorManager", &ErrorSingleton::AppWariningRegister());

    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();

}
