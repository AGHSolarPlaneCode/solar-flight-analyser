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

    ErrorSingleton::AppWariningRegister() << "Urgent Error";
    ErrorSingleton::AppWariningRegister() << "Information";
    ErrorSingleton::AppWariningRegister() << "Inherit Error";
    ErrorSingleton::AppWariningRegister() << "Access denied";
    ErrorSingleton::AppWariningRegister() << "Warning";
    ErrorSingleton::AppWariningRegister() << "Urgent Error";
    ErrorSingleton::AppWariningRegister() << "Information";
    ErrorSingleton::AppWariningRegister() << "Inherit Error";
    ErrorSingleton::AppWariningRegister() << "Access denied";
    ErrorSingleton::AppWariningRegister() << "Warning";

    ErrorSingleton::showErrorsQueue();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    ///engine.rootContext()->setContextProperty("errorManager", &ErrorSingleton::AppWariningRegister());

    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();

}
