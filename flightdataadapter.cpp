#include "flightdataadapter.h"
#include <QDebug>

FlightDataAdapter::FlightDataAdapter(QObject *parent) : QObject(parent)
{}


void FlightDataAdapter::SetFlightData(FlightData newData){
    data = newData;
    emit flightDataChanged();
}

void FlightDataAdapter::reciveReq(){
    emit sendLocationToWeather(QGeoCoordinate(data.Lat/10000000.0, data.Lon/10000000.0));
}

double FlightDataAdapter::TimeBootMs() const{
    return static_cast<int>(data.TimeBootMs);
}
double FlightDataAdapter::Lat () const{
    return data.Lat;
}
double FlightDataAdapter::Lon () const{
    return data.Lon;
}
double FlightDataAdapter::Alt () const{
    return data.Alt;
}
double FlightDataAdapter::RelativeAlt () const{
    return data.RelativeAlt;
}
double FlightDataAdapter::Vx () const{
    return data.Vx;
}
double FlightDataAdapter::Vy () const{
    return data.Vy;
}
double FlightDataAdapter::Vz () const{
    return data.Vz;
}
double FlightDataAdapter::Hdg () const{
    return static_cast<int>(data.Hdg);
}
