#ifndef FLIGHTDATAWORKER_H
#define FLIGHTDATAWORKER_H

#include <QObject>
#include <servermanager.h>
#include <flightdataadapter.h>

class FlightDataWorker : public QObject
{
    Q_OBJECT
public:
    explicit FlightDataWorker(QObject *parent = nullptr);
signals:
    void finished();
public slots:
    void start();
private:
    ServerManager servermanager{this};
    FlightDataAdapter adapter{this};
};

#endif // FLIGHTDATAWORKER_H
