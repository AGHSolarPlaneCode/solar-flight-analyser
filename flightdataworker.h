#ifndef FLIGHTDATAWORKER_H
#define FLIGHTDATAWORKER_H

#include <QObject>
#include <servermanager.h>
#include <flightdatastruct.h>

class FlightDataWorker : public QObject
{
    Q_OBJECT
public:
    explicit FlightDataWorker(QObject *parent = nullptr);
signals:
    void finished(FlightData);
public slots:
    void start();
    void setUrl(const QUrl& qUrl);
private:
    ServerManager servermanager{QString("localhost:8080/gps"),this};
    FlightData data;
};

#endif // FLIGHTDATAWORKER_H
