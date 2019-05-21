#include "jsonmanager.h"

/*

```GET /gps```
```json
{
    "TimeBootMs":0,
    "Lat":0,
    "Lon":0,
    "Alt":0,
    "RelativeAlt":0,
    "Vx":0,
    "Vy":0,
    "Vz":0,
    "Hdg":0
}

*/

JSONManager::JSONManager(QObject *parent) : QObject(parent), get(GET_STATE::WAITING)
  ,json_state(JSON_STATE::UNPARSED)
{

}

void JSONManager::ifDownload(bool state){
    if(state){
        resetFrame();
        get = GET_STATE::DOWNLOADED;
        json_state = JSON_STATE::UNPARSED;
    }
}
QByteArray JSONManager::getRawFrame(){
        return frame;
}
FlightData JSONManager::getReadyFlightData(){
        return data;
}

void JSONManager::setFlightData(const QJsonObject& object){

    //qDebug()<<object;  // uncomment to show raw json

    data.TimeBootMs = object.value("TimeBootMs").toDouble();
    data.Lat = object.value("Lat").toDouble();
    data.Lon = object.value("Lon").toDouble();
    data.RelativeAlt = object.value("Alt").toDouble();
    data.Vx = object.value("RelativeAlt").toDouble();
    data.Vy = object.value("Vx").toDouble();
    data.Vz = object.value("Vy").toDouble();
    data.Vz = object.value("Vz").toDouble();
    data.Hdg = object.value("Hdg").toDouble();

}

void JSONManager::parseJSON(const QByteArray& rawData){
    // parsing frame
    // add error handling to json
    // after parse set for WAITING and PARSED
    //qDebug()<<rawData;
    using ParseError = QJsonParseError;
    if(!rawData.isEmpty())
        frame = rawData;
    else{
        json_state = JSON_STATE::UNPARSED;
        emit errorSender(ErrorManager::JSONErrors::EMPTY);

        // emit signal with error
    }

    ParseError jerr;
    auto jsonDoc(QJsonDocument::fromJson(frame,&jerr));

    if( jerr.error == ParseError::NoError){
        auto object(jsonDoc.object());
        setFlightData(object);
        json_state = JSON_STATE::PARSED;
    }
    else{
        json_state = JSON_STATE::UNPARSED;
        emit errorSender(ErrorManager::JSONErrors::JSON, jerr);
        // emit signal with error
    }
}
