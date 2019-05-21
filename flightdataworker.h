#ifndef FLIGHTDATAWORKER_H
#define FLIGHTDATAWORKER_H

#include <QObject>
#include <servermanager.h>
#include <flightdatastruct.h>
#include "errorhandler.h"

class FlightDataWorker : public QObject
{
    Q_OBJECT
public:
    explicit FlightDataWorker(QObject *parent = nullptr);
    ErrorManager* passErrors();
signals:
    void finished(FlightData);
public slots:
    void start();
    void setUrl(const QUrl& qUrl);
private:
    ServerManager servermanager{QString("localhost:8080/gps"), this};  // example ->  localhost:8080/gpshttps://json-ld.org/contexts/person
    FlightData data;
};

#endif // FLIGHTDATAWORKER_H
