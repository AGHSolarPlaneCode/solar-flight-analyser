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


JSONManager::JSONManager(QObject *parent) : QObject(parent), err(),get(GET_STATE::WAITING)
  ,json_state(JSON_STATE::UNPARSED)
{

}

void JSONManager::ifDownload(bool state){
    if(true == state){
        resetFrame();
        get = GET_STATE::DOWNLOADED;
        json_state = JSON_STATE::UNPARSED;
    }
}

FlightData JSONManager::getReadyFlightData(){
        return data;
}

void JSONManager::setFlightData(const QJsonObject& object){
    // temporary
    qDebug()<<object.value("TimeBootMs");
    qDebug()<<object.value("Lat");
    qDebug()<<object.value("Lon");
    qDebug()<<object.value("Alt");
    qDebug()<<object.value("RelativeAlt");
    qDebug()<<object.value("Vx");
    qDebug()<<object.value("Vy");
    qDebug()<<object.value("Vz");
    qDebug()<<object.value("Hdg");

}
void JSONManager::getJSON(const QByteArray& json){
    if(!json.isEmpty() && json != frame)
        frame = json;
    else{
        err = std::move(JsonError(JsonError::Errors::EMPTY));
        throw(err);
    }
}

void JSONManager::parseJSON(){
    // parsing frame
    // add error handling to json
    // after parse set for WAITING and PARSED
    using ParseError = QJsonParseError;

    ParseError jerr;
    auto jsonDoc(QJsonDocument::fromJson(frame,&jerr));

    if( jerr.error != ParseError::NoError){
        auto object(jsonDoc.object());
        setFlightData(object);
        json_state = JSON_STATE::PARSED;
    }
    else{
        json_state = JSON_STATE::UNPARSED;
        err = std::move(JsonError(JsonError::Errors::JSON,jerr));
        throw(err);
    }



}
