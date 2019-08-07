#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H
#include <tuple>

namespace Data{
    struct TelemetryData{
        double Lat;
        double Lon;
        double latRaw;
        double lonRaw;
        double Alt;
        double RelativeAlt;
        double Vx;
        double Vy;
        double Vz;
        double Hdg;
        double Row;
        double Pitch;
        double Yaw;
        double RollSpeed;
        double PitchSpeed;
        double YawSpeed;
        bool operator==(const TelemetryData& compData){

            return std::tie(Lat,Lon,latRaw,lonRaw,Alt,
                            RelativeAlt,Vx,Vy,Vz,Hdg,Row,
                            Pitch,Yaw,RollSpeed,PitchSpeed,YawSpeed) ==
                   std::tie(compData.Lat, compData.Lon, compData.latRaw,
                            compData.lonRaw, compData.Alt, compData.RelativeAlt,
                            compData.Vx,compData.Vy,compData.Vz,compData.Hdg,compData.Row,
                            compData.Pitch, compData.Yaw,compData.RollSpeed,
                            compData.PitchSpeed,compData.YawSpeed);
        }

        TelemetryData& operator=(const TelemetryData& comp){
            if(this == &comp)
                return *this;
            Lat         = comp.Lat;
            Lon         = comp.Lon;
            latRaw      = comp.latRaw;
            lonRaw      = comp.lonRaw;
            Alt         = comp.Alt;
            RelativeAlt = comp.RelativeAlt;
            Vx          = comp.Vx;
            Vy          = comp.Vy;
            Vz          = comp.Vz;
            Hdg         = comp.Hdg;
            Row         = comp.Row;
            Pitch       = comp.Pitch;
            Yaw         = comp.Yaw;
            RollSpeed   = comp.PitchSpeed;
            YawSpeed    = comp.YawSpeed;

            return *this;
        }
    };
}

#endif // FLIGHTDATA_H
