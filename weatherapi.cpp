#include "weatherapi.h"

WeatherAPI::WeatherAPI(QObject *parent) : QObject(parent), src(nullptr),
    qmlState(true), gpsObtained(false), connectionError(false),
    type(Connection::PLANE), firstReq(false)
{
    establishConnection();
}

// - JSON EXAMPLE

//  {"coord":{"lon":139,"lat":35},

//  "sys":{"country":"JP","sunrise":1369769524,"sunset":1369821049},

//  "weather":[{"id":804,"main":"clouds","description":"overcast clouds","icon":"04n"}],

//  "main":{"temp":289.5,"humidity":89,"pressure":1013,"temp_min":287.04,"temp_max":292.04},

//  "wind":{"speed":7.31,"deg":187.002},

//  "rain":{"3h":0},

//  "clouds":{"all":92},

//  "dt":1369824698,

//  "id":1851632,

//  "name":"Shuzenji",

//  "cod":200}


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

void WeatherAPI::obtainUserLocation(){

    auto positionUpdate([this](QGeoPositionInfo pos){
       coord = pos.coordinate();
       if(this->useGpsDevice())
           this->refreshWeather();
    });

    auto positionError([this](QGeoPositionInfoSource::Error e){
        // send string Q_PROPERTY with information about change localisation
        connectionError = true;
        gpsObtained = false;
        disconnect(src, &QGeoPositionInfoSource::positionUpdated, nullptr, nullptr);  // check correctness
        src->stopUpdates();
        src->deleteLater();

        this->setLocStatus(false);

    });

    if(src){
        connect(src, &QGeoPositionInfoSource::positionUpdated, positionUpdate);
        // position error change to PLANE l ocation, immediately
        connect(src, SIGNAL(error(QGeoPositionInfoSource::Error e)), SLOT(positionError));
        gpsObtained = true;
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

void WeatherAPI::establishConnection(){
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

QString WeatherAPI::getTemp() const{
    return data.temp;
}

QString WeatherAPI::getDescription() const{
    return data.description;
}

QString WeatherAPI::getIconID() const{
    return data.iconID;
}

double WeatherAPI::getHumidity() const{
    return data.humidity;
}

double WeatherAPI::getWindSpeed() const{
    return data.windSpeed;
}

void WeatherAPI::getWeatherData(QNetworkReply* reply){
    if(QNetworkReply::NoError == reply->error()){
        // parsing json
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

        if(doc.isObject()){
            QJsonObject obj = doc.object();
            QJsonObject tmp;
            QJsonValue val;
            if(obj.contains(QStringLiteral("weather"))){
                    val = obj.value(QStringLiteral("weather"));

                    QJsonArray array = val.toArray();
                    val = array.at(0);
                    tmp = val.toObject();

                    data.description = tmp.value(QStringLiteral("description")).toString();

                    data.iconID = tmp.value(QStringLiteral("icon")).toString();
            }
            if(obj.contains(QStringLiteral("main"))){
                val = obj.value(QStringLiteral("main"));
                tmp = val.toObject();
                val = tmp.value(QStringLiteral("temp"));

                data.temp = QString::number(val.toDouble());

                data.humidity = tmp.value(QStringLiteral("humidity")).toDouble();
            }
            if(obj.contains(QStringLiteral("wind"))){
                val = obj.value(QStringLiteral("wind"));
                tmp = val.toObject();

                data.windSpeed = tmp.value(QStringLiteral("speed")).toDouble();
            }
        }
    }
    else{
        qDebug()<<"Error service";
    }
}

WeatherAPI::~WeatherAPI(){ // close all connections
    // stop connection
}
