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
    RegisterError(WindowType::MainAppWindow, ErrorMessage::WARINING) << "Urgent Error";
    RegisterError(WindowType::MainAppWindow, ErrorMessage::WARINING) << "Information";
    RegisterError(WindowType::MainAppWindow, ErrorMessage::WARINING) << "Inherit Error";
    RegisterError(WindowType::MainAppWindow, ErrorMessage::WARINING) << "Access denied";
    RegisterError(WindowType::MainAppWindow, ErrorMessage::WARINING) << "Warning";


    ErrorSingleton::showErrorsQueue();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    ///engine.rootContext()->setContextProperty("errorManager", &ErrorSingleton::AppWariningRegister());

    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();

}
