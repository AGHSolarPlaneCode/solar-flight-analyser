#include "flightdataworker.h"
#include <QtDebug>
#include <QThread>

FlightDataWorker::FlightDataWorker(QObject *parent) : QObject(parent)
{

}

void FlightDataWorker::setUrl(const QUrl& qUrl)
{
    servermanager.setUrl(qUrl);
}

void FlightDataWorker::start(){
    try {
        qDebug()<<"From worker thread: "<<QThread::currentThreadId();
        servermanager.update();
        qDebug()<<"Finished sleeping";
        data = servermanager.getData();
    } catch (std::exception e) {
        qDebug()<<e.what();
    }
    emit finished(data);
}

ErrorManager* FlightDataWorker::passErrors(){
    return servermanager.getErrorManager();
}
