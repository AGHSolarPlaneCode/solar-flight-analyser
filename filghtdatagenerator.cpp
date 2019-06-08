#include "filghtdatagenerator.h"



// default data
FlightData::Generator::FlightDataGenerator::FlightDataGenerator(const QGeoCoordinate& firstPos,
    const QGeoCoordinate& lastPos, QObject* parent): QObject(parent), weatherTimer(new QTimer(this)),
    flyData{firstPos,firstPos,lastPos,0.0,0.0, firstPos.distanceTo(lastPos)/Data::Param::KM},
    weatherData{1,0.0} {
    connect(weatherTimer, &QTimer::timeout, this,&FlightDataGenerator::weatherDataGenerator);

    weatherTimer->setInterval(10000);
    weatherTimer->start();

    //qDebug() << flyData.startPoint.distanceTo(flyData.endPoint) /1000;
}

// Descript:

// firstPos -> Cracow
// lastPos  -> Gdansk


// FlyData{
//    QGeoCoordinate lastPosition          < - last known position
//    QGeoCoordinate startPoint, endPoint  < - start and end point(Cracow/Gdansk)
//    double alt
//    double speed
//    double distanceToGoal
// }

// WeatherData{
//    int iconID
//    double temp
//    double humidity
//    double windSpeed
//    QString description
// }

void FlightData::Generator::FlightDataGenerator::setPoint(const QGeoCoordinate& point){
    if(flyData.lastPosition == point)
        return;

    flyData.lastPosition = point;

    if(flyData.lastPosition == flyData.endPoint)
        std::swap(flyData.startPoint, flyData.endPoint);

    setDistanceToPoint(flyData.lastPosition);

    emit movePosition();  // emit signal about moving position
}

void FlightData::Generator::FlightDataGenerator::setDistanceToPoint(const QGeoCoordinate& point){
    if(!point.isValid())
        return;

    flyData.distanceToGoal = static_cast<double>(point.distanceTo(flyData.endPoint)) / Data::Param::KM;
}

void FlightData::Generator::FlightDataGenerator::weatherDataGenerator(){
    auto render([](auto a, auto b){ return std::uniform_int_distribution<int>(a,b); });


    weatherData.temp = render(20,24)(*QRandomGenerator::global());      // Celcius
    qDebug()<<"Temperature: "<<weatherData.temp;

    if(QTime::currentTime().hour() > 20)
        weatherData.iconID = 3;        // evening
    else
        weatherData.iconID = 1;        // day

    qDebug()<<"IconID: "<<weatherData.iconID;

    weatherData.humidity = render(30,33)(*QRandomGenerator::global());  // %
    qDebug()<<"Humidity: "<<weatherData.humidity;

    weatherData.windSpeed = render(4,10)(*QRandomGenerator::global());  // m/s
    qDebug()<<"WindSpeed: "<<weatherData.windSpeed;

    emit weatherSignal();
}
