#include "servermanager.h"
#include <QThread> //For testing only, remove on implementation

ServerManager::ServerManager(QObject *parent) : QObject(parent)
{

}

void ServerManager::Update(){
    QThread::msleep(30);
    FlightData dummy{
        10,
        20,
        45,
        1000,
        500,
        40,
        1,
        2,
        0
        /*uint32_t TimeBootMs;
        int32_t Lat;
        int32_t Lon;
        int32_t Alt;
        int32_t RelativeAlt;
        int16_t Vx;
        int16_t Vy;
        int16_t Vz;
        uint16_t Hdg;*/
    };
    data = dummy;
    return;
}

FlightData ServerManager::GetData(){
    return data;
}
