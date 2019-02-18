#include "flightdatacontroller.h"
#include <QtDebug>

FlightDataController::FlightDataController(QObject *parent) : QObject(parent)
{
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(StartWorkerIfFree()));
    QObject::connect(&worker, SIGNAL(finished(FlightData)), this, SLOT(workerHasFinished(FlightData)));
    QObject::connect(this, SIGNAL(StartWorker()), &worker, SLOT(start()));
    QObject::connect(this, SIGNAL(SetWorkerURL(const QUrl&)), &worker, SLOT(setUrl(const QUrl &)));

    QObject::connect(this, SIGNAL(StartClock(int)), &timer, SLOT(start(int)));
    QObject::connect(this, SIGNAL(StopClock()),&timer,SLOT(stop()));
    worker.moveToThread(&thread);
    thread.start();
}

void FlightDataController::StartWorkerIfFree(){
    if(workerIsFree){
        emit StartWorker();
        workerIsFree = false;
    }
    else{
        //qDebug()<<"Worker was busy";
    }
}

void FlightDataController::workerHasFinished(FlightData data){
    adapter.SetFlightData(data);
    workerIsFree = true;
}

void FlightDataController::doUpdates(bool startflag){
    if (startflag){
        emit StartClock(500);
    } else {
        emit StopClock();
    }
}

void FlightDataController::setUrl(QString url)
{
    emit SetWorkerUrl(QUrl(url));
}

FlightDataAdapter * FlightDataController::getAdapter(){
    return &adapter;
}
