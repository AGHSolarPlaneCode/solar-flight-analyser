#ifndef FLIGHTDATAADAPTER_H
#define FLIGHTDATAADAPTER_H

#include <QObject>
#include <QTimer>
#include "flightdatastruct.h"
class FlightDataAdapter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int TimeBootMs READ TimeBootMs NOTIFY flightDataChanged)
    Q_PROPERTY(int Lat READ Lat NOTIFY flightDataChanged)
    Q_PROPERTY(int Lon READ Lon NOTIFY flightDataChanged)
    Q_PROPERTY(int Alt READ Alt NOTIFY flightDataChanged)
    Q_PROPERTY(int RelativeAlt READ RelativeAlt NOTIFY flightDataChanged)
    Q_PROPERTY(int Vx READ Vx NOTIFY flightDataChanged)
    Q_PROPERTY(int Vy READ Vy NOTIFY flightDataChanged)
    Q_PROPERTY(int Vz READ Vz NOTIFY flightDataChanged)
    Q_PROPERTY(int Hdg READ Hdg NOTIFY flightDataChanged)
public:
    explicit FlightDataAdapter(QObject *parent = nullptr);
    void SetFlightData(FlightData newData);

    int TimeBootMs() const;
    int Lat () const;
    int Lon () const;
    int Alt () const;
    int RelativeAlt () const;
    int Vx () const;
    int Vy () const;
    int Vz () const;
    int Hdg () const;

signals:
    void flightDataChanged();
    void sendLocationToWeather(QPair<int, int> Location);
public slots:
    void weatherTimeout();
private:
    FlightData data;
    QTimer weatherTimer{this};
};

#endif // FLIGHTDATAADAPTER_H
