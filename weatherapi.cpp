#include "weatherapi.h"

WeatherAPI::WeatherAPI(QObject *parent) : QObject(parent), src(nullptr),
    qmlState(true), gpsObtained(false), connectionError(false),
    type(Connection::PLANE), firstReq(false)
{
    establishConnection();
}

void WeatherAPI::getPlaneCoordinates(const QGeoCoordinate& pos){
    if(pos == coord)
        return;
    coord = pos;
    refreshWeather();
}

bool WeatherAPI::isUserLocation(){
    return Connection::USER == type;
}

bool WeatherAPI::isPlaneLocation(){
    return Connection::PLANE == type;
}

void WeatherAPI::setLocStatus(bool state){
    if(state){
        type = Connection::PLANE;
        qmlState = state;
        emit locStatusChanged();
    }
    else{
        type = Connection::USER;
        qmlState = state;
        emit locStatusChanged();
    }
    manageConnections();
}

bool WeatherAPI::useGpsDevice(){
    auto cond([this]()-> bool {return type == Connection::USER &&
    gpsObtained == true && qmlState == false;});

    return cond();
}

void WeatherAPI::manageConnections(){          // - main method to manage connections
    if(isPlaneLocation()){
        // stop UserLoc
        if(gpsObtained)
            src->stopUpdates();
        // run PlaneLoc
        reqTimer->start(1000);
    }
    else if(isUserLocation()){
        // stop PlaneLoc
        reqTimer->stop();
        firstReq = false;
        // run UserLoc
       if(!gpsObtained)
           obtainUserLocation();

       src->setUpdateInterval(10*60*1000);       // update every 10 min
       src->startUpdates();                      // start update

    }
    else{
        qDebug()<<"Bad connection!";
    }
}

QGeoCoordinate WeatherAPI::getCoordinate(){
    return coord;
}

void WeatherAPI::obtainUserLocation(){ // turn on only when user set this in qml
    src = QGeoPositionInfoSource::createDefaultSource(this);

    auto positionUpdate([this](QGeoPositionInfo pos){
       coord = pos.coordinate();
       if(this->useGpsDevice())        // forst positionUpdate doesn't refresh Weather
           this->refreshWeather();
    });

    auto positionError([this](QGeoPositionInfoSource::Error e){
        // send string Q_PROPERTY with information about change localisation
        connectionError = true;      // if true (we should involve this func once again <- in refresh weather)
        gpsObtained = false;
        disconnect(src, &QGeoPositionInfoSource::positionUpdated, nullptr, nullptr);  // check correctness
        src->stopUpdates();
        src->deleteLater();

        this->setLocStatus(false);   // change for plane weather

    });

    if(src){
        connect(src, &QGeoPositionInfoSource::positionUpdated, positionUpdate);
        // position error change to PLANE l ocation, immediately
        connect(src, SIGNAL(error(QGeoPositionInfoSource::Error e)), SLOT(positionError));
        gpsObtained = true;

        //src->setUpdateInterval(10*60*1000);
        //src->startUpdates();
    }

}

void WeatherAPI::setQueryProperties(){
    QString lon, lat;
    endpoint = "http://api.openweathermap.org/data/2.5/weather";

    lon.setNum(coord.longitude());
    lat.setNum(coord.latitude());

    query.addQueryItem("lat",lat);
    query.addQueryItem("lon",lon);
    query.addQueryItem("mode","json");
    query.addQueryItem("APPID","***");       // - press your own API key
    endpoint.setQuery(query);
}

void WeatherAPI::establishConnection(){      // - only one involve (default)
    network = new QNetworkAccessManager(this);
    reqTimer = new QTimer(this);

    // lambda for emit signal

    auto emitter([this](){
        if(!firstReq){    // false - interval  = 1s | true interval = 10s
            reqTimer->setInterval(10*60*1000); // - set interval to 10 min
            firstReq = true;
        }
        emit reqSender(); });

    QObject::connect(reqTimer, &QTimer::timeout, emitter);
    QObject::connect(network, &QNetworkAccessManager::finished, this, &WeatherAPI::getWeatherData);

    reqTimer->start(1000);
}

void WeatherAPI::refreshWeather(){
    setQueryProperties();
    request.setUrl(endpoint);
    network->get(request);
}

void WeatherAPI::getWeatherData(QNetworkReply* reply){
    if(QNetworkReply::NoError == reply->error()){
        // parsing json
    }
    else{

    }
}
