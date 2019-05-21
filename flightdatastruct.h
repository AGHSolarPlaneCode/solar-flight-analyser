#ifndef FLIGHTDATASTRUCT_H
#define FLIGHTDATASTRUCT_H

#include<cstdint> //Nie wiem czy nie zmienic na normalne typy

typedef struct flightData{
    double TimeBootMs;
    double Lat;
    double Lon;
    double Alt;
    double RelativeAlt;
    double Vx;
    double Vy;
    double Vz;
    double Hdg;
} FlightData;

#endif // FLIGHTDATASTRUCT_H
