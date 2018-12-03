#include "flightdataadapter.h"

FlightDataAdapter::FlightDataAdapter(QObject *parent) : QObject(parent)
{

}

void FlightDataAdapter::SetFlightData(FlightData newData){
    data = newData;
    emit flightDataChanged();
}

uint32_t FlightDataAdapter::TimeBootMs() const{
    return data.TimeBootMs;
}
int32_t FlightDataAdapter::Lat () const{
return data.Lat;
}
int32_t FlightDataAdapter::Lon () const{
    return data.Lon;
}
int32_t FlightDataAdapter::Alt () const{
    return data.Alt;
}
int32_t FlightDataAdapter::RelativeAlt () const{
    return data.RelativeAlt;
}
int16_t FlightDataAdapter::Vx () const{
    return data.Vx;
}
int16_t FlightDataAdapter::Vy () const{
    return data.Vy;
}
int16_t FlightDataAdapter::Vz () const{
    return data.Vz;
}
uint16_t FlightDataAdapter::Hdg () const{
    return data.Hdg;
}
