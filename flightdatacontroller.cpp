#include "flightdatacontroller.h"
#include <QtDebug>

FlightDataController::FlightDataController(QObject *parent) : QObject(parent)
{
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(StartWorkerIfFree()));
    QObject::connect(&worker, SIGNAL(finished(FlightData)), this, SLOT(workerHasFinished(FlightData)));
    QObject::connect(this, SIGNAL(StartWorker()), &worker, SLOT(start()));
    QObject::connect(this, &FlightDataController::SetWorkerUrl, &worker, &FlightDataWorker::setUrl);

    QObject::connect(this, SIGNAL(StartClock(int)), &timer, SLOT(start(int)));
    QObject::connect(this, SIGNAL(StopClock()),&timer,SLOT(stop()));
    worker.moveToThread(&thread);
    thread.start();
}

bool FlightDataController::initializeQMLObjects(){
    qRegisterMetaType<FlightData>("FlightData");
    //std::unique_ptr<FlightDataController> controller(std::make_unique<FlightDataController>());

    //FlightDataController *controller = new FlightDataController();

    WeatherAPI *weather = new WeatherAPI(); //instance of weatherAPI - for test


    engine.rootContext()->setContextProperty("controller", this);
    engine.rootContext()->setContextProperty("adapter", getAdapter());
    engine.rootContext()->setContextProperty("error", getError());
    engine.rootContext()->setContextProperty("weatherAPIAdapter", weather); //context for QPROPERTY

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return false;
    else
        return true;
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

ErrorManager* FlightDataController::getError(){
    return worker.passErrors();
}
