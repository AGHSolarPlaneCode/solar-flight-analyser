#ifndef FLIGHTDATAADAPTER_H
#define FLIGHTDATAADAPTER_H

#include <QObject>
#include "flightdatastruct.h"
class FlightDataAdapter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint32_t TimeBootMs READ TimeBootMs NOTIFY flightDataChanged)
    Q_PROPERTY(int32_t Lat READ Lat NOTIFY flightDataChanged)
    Q_PROPERTY(int32_t Lon READ Lon NOTIFY flightDataChanged)
    Q_PROPERTY(int32_t Alt READ Alt NOTIFY flightDataChanged)
    Q_PROPERTY(int32_t RelativeAlt READ RelativeAlt NOTIFY flightDataChanged)
    Q_PROPERTY(int16_t Vx READ Vx NOTIFY flightDataChanged)
    Q_PROPERTY(int16_t Vy READ Vy NOTIFY flightDataChanged)
    Q_PROPERTY(int16_t Vz READ Vz NOTIFY flightDataChanged)
    Q_PROPERTY(uint16_t Hdg READ Hdg NOTIFY flightDataChanged)
public:
    explicit FlightDataAdapter(QObject *parent = nullptr);
    void SetFlightData(FlightData newData);

    uint32_t TimeBootMs() const;
    int32_t Lat () const;
    int32_t Lon () const;
    int32_t Alt () const;
    int32_t RelativeAlt () const;
    int16_t Vx () const;
    int16_t Vy () const;
    int16_t Vz () const;
    uint16_t Hdg () const;

signals:
    void flightDataChanged();
public slots:
private:
    FlightData data;
};

#endif // FLIGHTDATAADAPTER_H
/*
uint32_t TimeBootMs;
int32_t Lat;
int32_t Lon;
int32_t Alt;
int32_t RelativeAlt;
int16_t Vx;
int16_t Vy;
int16_t Vz;
uint16_t Hdg;
*/
