#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#define ZERO_KELVIN 273.15

#include <QString>
#include <QPair>

class WeatherData
{
public:
    friend class WeatherAPI;
    explicit WeatherData();
    WeatherData(const WeatherData& data);
    WeatherData& operator=(const WeatherData& data);
    QString getCelciusTemp();
private:
    QString temp;
    QString description;
    QPair<QString, QString > coordinate;
    QString iconID;
    double humidity;
    double windSpeed;
};

#endif // WEATHERDATA_H
