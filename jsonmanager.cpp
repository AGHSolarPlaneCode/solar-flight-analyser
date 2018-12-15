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
    if(true == state){
        resetFrame();
        get = GET_STATE::DOWNLOADED;
        json_state = JSON_STATE::UNPARSED;
    }
}

FlightData JSONManager::getReadyFlightData(){
        return data;
}

void JSONManager::parseJSON(){
    // parsing frame
    // add error handling to json
    // after parse set for WAITING and PARSED
    if(!frame.isEmpty()){
        QJsonDocument jsonDoc(QJsonDocument::fromJson(frame));
        auto object(jsonDoc.object());

        // temporary
        qDebug()<< object.value("TimeBootMs");
        qDebug() << object.value("Lat");
        qDebug() << object.value("Lon");
        qDebug() << object.value("Alt");
        qDebug() << object.value("RelativeAlt");
        qDebug() << object.value("Vx");
        qDebug() << object.value("Vy");
        qDebug() << object.value("Vz");
        qDebug() << object.value("Hdg");

        json_state = JSON_STATE::PARSED;
    }else{
        //temporary
        json_state = JSON_STATE::UNPARSED;
        qDebug() << "Frame is empty!";
        return;
    }
}
