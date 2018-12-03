#ifndef FLIGHTDATACONTROLLER_H
#define FLIGHTDATACONTROLLER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "flightdataworker.h"

/*This class:
 * Makes a worker
 * Starts a thread
 * Sets a timer
 * On every timer cycle:
 * -checks if worker is free
 * -if free tells the worker to do work
*/

class FlightDataController : public QObject
{
    Q_OBJECT
public:
    explicit FlightDataController(QObject *parent = nullptr);

signals:
    void StartWorker();
public slots:
    void workerHasFinished();
    void StartWorkerIfFree();

private:
    bool workerIsFree = true;
    FlightDataWorker worker;
    QThread thread;
    QTimer timer;
};

#endif // FLIGHTDATACONTROLLER_H
