#include "flightdatacontroller.h"
#include <QtDebug>

FlightDataController::FlightDataController(QObject *parent) : QObject(parent)
{


    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(StartWorkerIfFree()));
    QObject::connect(&worker, SIGNAL(finished()), this, SLOT(workerHasFinished()));
    QObject::connect(this, SIGNAL(StartWorker()), &worker, SLOT(start()));

    timer.start(30);
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

void FlightDataController::workerHasFinished(){
    workerIsFree = true;
}
