#include "weatherdata.h"

WeatherData::WeatherData(): temp("-"),description("---"),
    coordinate(qMakePair(QStringLiteral("-"),QStringLiteral("-"))), iconID("--"),humidity(0.0), windSpeed(0.0) {}

WeatherData::WeatherData(const WeatherData& data){
    temp = data.temp;
    description = data.description;
    coordinate = data.coordinate;
    iconID = data.iconID;
    humidity = data.humidity;
    windSpeed = data.windSpeed;
}

WeatherData& WeatherData::operator=(const WeatherData& data){
    if(this == &data)
        return *this;

    temp = data.temp;
    description = data.description;
    coordinate = data.coordinate;
    iconID = data.iconID;
    humidity = data.humidity;
    windSpeed = data.windSpeed;
}

QString WeatherData::getCelciusTemp(){
    return QString::number(qRound(temp.toInt() - ZERO_KELVIN)) + QChar(0xB0);
}

void WeatherData::showWeather(){
    qDebug()<<temp;
    qDebug()<<description;
    qDebug()<<iconID;
    qDebug()<<humidity;
    qDebug()<<windSpeed;
}
