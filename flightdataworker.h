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
    FlightDataAdapter* getAdapter();
private:
    ServerManager servermanager{QString("localhost:8080/gps"),this};
    FlightDataAdapter adapter{this};
};

#endif // FLIGHTDATAWORKER_H
