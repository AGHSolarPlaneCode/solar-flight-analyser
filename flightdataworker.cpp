#include "flightdataworker.h"
#include <QtDebug>
#include <QThread>

FlightDataWorker::FlightDataWorker(QObject *parent) : QObject(parent)
{

}

void FlightDataWorker::start(){
    try {
        //qDebug()<<"From worker thread: "<<QThread::currentThreadId();
        servermanager.Update();
        //qDebug()<<"Finished sleeping";
        adapter.SetFlightData(servermanager.GetData());
    } catch (std::exception e) {
        qDebug()<<e.what();
    }
    emit finished();
}
