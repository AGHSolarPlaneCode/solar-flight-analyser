#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H
#include <tuple>
#include <QDebug>

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
        double gndSpeed;

        bool operator==(const TelemetryData& compData){

            return std::tie(Lat,Lon,latRaw,lonRaw,Alt,
                            RelativeAlt,Vx,Vy,Vz,Hdg,Row,
                            Pitch,Yaw,RollSpeed,PitchSpeed,YawSpeed, gndSpeed) ==
                   std::tie(compData.Lat, compData.Lon, compData.latRaw,
                            compData.lonRaw, compData.Alt, compData.RelativeAlt,
                            compData.Vx,compData.Vy,compData.Vz,compData.Hdg,compData.Row,
                            compData.Pitch, compData.Yaw,compData.RollSpeed,
                            compData.PitchSpeed,compData.YawSpeed, gndSpeed);
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
            gndSpeed    = comp.gndSpeed;

            return *this;
        }

        friend QDebug operator<<(QDebug debug, const TelemetryData& tData){
            debug << "Lat: "         << tData.Lat;
            debug << "Lon: "         << tData.Lon;
            debug << "rawLat: "      << tData.latRaw;
            debug << "rawLon: "      << tData.lonRaw;
            debug << "Alt: "         << tData.Alt;
            debug << "RelativeAlt: " << tData.RelativeAlt;
            debug << "Vx: "          << tData.Vx;
            debug << "Vy: "          << tData.Vy;
            debug << "Vz: "          << tData.Vz;
            debug << "Hdg: "         << tData.Hdg;
            debug << "Row: "         << tData.Row;
            debug << "Pitch: "       << tData.Pitch;
            debug << "Yaw: "         << tData.Yaw;
            debug << "RollSpeed: "   << tData.RollSpeed;
            debug << "YawSpeed: "    << tData.YawSpeed;
            debug << "gndSpeed: "    << tData.gndSpeed;

            return debug;
        }

    };
}

#endif // FLIGHTDATA_H
