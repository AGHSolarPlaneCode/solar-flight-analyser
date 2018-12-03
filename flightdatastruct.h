#ifndef FLIGHTDATASTRUCT_H
#define FLIGHTDATASTRUCT_H

#include<cstdint> //Nie wiem czy nie zmienic na normalne typy

typedef struct flightData{
    uint32_t TimeBootMs;
    int32_t Lat;
    int32_t Lon;
    int32_t Alt;
    int32_t RelativeAlt;
    int16_t Vx;
    int16_t Vy;
    int16_t Vz;
    uint16_t Hdg;
} FlightData;

#endif // FLIGHTDATASTRUCT_H
