#include "filghtdatagenerator.h"



// default data
FlightData::Generator::FlightDataGenerator::FlightDataGenerator(const QGeoCoordinate& firstPos,
    const QGeoCoordinate& lastPos, QObject* parent): QObject(parent),
    flyData{firstPos,firstPos,lastPos,0.0,0.0,0.0},
    weatherData{1,0.0} {
    //qDebug() << flyData.startPoint.distanceTo(flyData.endPoint) /1000;
}

// Descript:

// firstPos -> Cracow
// lastPos -> Gdansk


// FlyData{
//    QGeoCoordinate lastPosition          < - last known position
//    QGeoCoordinate startPoint, endPoint  < - start and end point(Cracow/Gdansk)
//    double alt
//    double speed
//        }

// WeatherData{
//    int iconID
//    double temp
// }

void FlightData::Generator::FlightDataGenerator::setPoint(const QGeoCoordinate& point){
    if(flyData.lastPosition == point)
        return;
    flyData.lastPosition = point;

    setDistanceToPoint(flyData.lastPosition);

    generateData();

    emit movePosition();  // emit signal about moving position
}

void FlightData::Generator::FlightDataGenerator::setDistanceToPoint(const QGeoCoordinate& point){
    if(!point.isValid())
        return;

    flyData.distanceToGoal = static_cast<double>(flyData.endPoint.distanceTo(point)) / Data::Param::KM;
    qDebug()<<flyData.distanceToGoal;
}

void FlightData::Generator::FlightDataGenerator::generateData(){
    // generate data for interface
}
