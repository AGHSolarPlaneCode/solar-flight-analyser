#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#define ZERO_KELVIN 273.15

#include <QObject>
#include <QPair>

class WeatherData : public QObject
{
    Q_OBJECT
public:
    friend class WeatherAPI;
    explicit WeatherData(QObject *parent = nullptr);
    WeatherData(const WeatherData& data);
    WeatherData& operator=(const WeatherData& data);
    QString getCelciusTemp();
signals:

public slots:

private:
    QString temp;
    QString description;
    QPair<QString, QString > coordinate;
    QString iconID;
    double humidity;
    double windSpeed;
};

#endif // WEATHERDATA_H
