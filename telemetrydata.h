#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

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
    };
}

#endif // FLIGHTDATA_H
