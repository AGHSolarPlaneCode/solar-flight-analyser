#include "filghtdatagenerator.h"



// default data
FlightData::Generator::FlightDataGenerator::FlightDataGenerator(const QGeoCoordinate& firstPosition,
    const QGeoCoordinate& lastPosition, QObject* parent): QObject(parent), flyData{lastPosition,firstPosition,lastPosition,0.0,0.0},
    weatherData{1,0.0} {}



// FlyData{
//    QGeoCoordinate lastPosition;
//    QGeoCoordinate startPoint, endPoint;
//    double alt;
//    double speed;
//};

// WeatherData{
//    int iconID;
//    double temp;
//};

void FlightData::Generator::FlightDataGenerator::setPoint(const QGeoCoordinate& point){
    if(flyData.lastPosition == point)
        return;
    flyData.lastPosition = point;
    generateData();
    emit movePosition();  // emit signal about moving position
}

void FlightData::Generator::FlightDataGenerator::generateData(){
    // generate data for interface
}
