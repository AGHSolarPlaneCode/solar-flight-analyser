#ifndef FLIGHTDATAADAPTER_H
#define FLIGHTDATAADAPTER_H

#include <QObject>
#include <QTimer>
#include <QGeoCoordinate>
#include "flightdatastruct.h"
#include <QGeoCoordinate>

class FlightDataAdapter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double TimeBootMs READ TimeBootMs NOTIFY flightDataChanged)
    Q_PROPERTY(double Lat READ Lat NOTIFY flightDataChanged)
    Q_PROPERTY(double Lon READ Lon NOTIFY flightDataChanged)
    Q_PROPERTY(double Alt READ Alt NOTIFY flightDataChanged)
    Q_PROPERTY(double RelativeAlt READ RelativeAlt NOTIFY flightDataChanged)
    Q_PROPERTY(double Vx READ Vx NOTIFY flightDataChanged)
    Q_PROPERTY(double Vy READ Vy NOTIFY flightDataChanged)
    Q_PROPERTY(double Vz READ Vz NOTIFY flightDataChanged)
    Q_PROPERTY(double Hdg READ Hdg NOTIFY flightDataChanged)
public:
    explicit FlightDataAdapter(QObject *parent = nullptr);
    void SetFlightData(FlightData newData);

    double TimeBootMs() const;
    double Lat () const;
    double Lon () const;
    double Alt () const;
    double RelativeAlt () const;
    double Vx () const;
    double Vy () const;
    double Vz () const;
    double Hdg () const;

signals:
    void flightDataChanged();
    void sendLocationToWeather(const QGeoCoordinate& coord);
public slots:
    void reciveReq();
private:
    FlightData data;
};

#endif // FLIGHTDATAADAPTER_H
