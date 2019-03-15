#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include "weatherdata.h"
#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QGeoCoordinate>
#include <QDebug>
#include <QPair>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QUrl>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

/* Wednesday plan */
// 1. Class for data (setters, getters)
// 2. Parsing JSON (slot) -> getWeatherData
// 3. Register class

class WeatherAPI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool locStatus READ getLocStatus WRITE setLocStatus NOTIFY locStatusChanged)

    Q_PROPERTY(QString temp READ getTemp())
    Q_PROPERTY(QString desc READ getDescription())
    Q_PROPERTY(QString iconID READ getIconID())
    Q_PROPERTY(double hum READ getHumidity())
    Q_PROPERTY(double windSpeed READ getWindSpeed())
public:

    enum class Connection{USER = 1, PLANE, DEFAULT};               // USER - obtain user location of device   PLANE - get location of plane, from DataAdapter
    explicit WeatherAPI(QObject *parent = nullptr);

    // - getters
    QString getTemp() const;
    QString getDescription() const;
    QString getIconID() const;
    double getHumidity() const;
    double getWindSpeed() const;

    bool getLocStatus(){ return qmlState; }
    void setLocStatus(bool state);
    bool isUserLocation();
    bool isPlaneLocation();
    bool useGpsDevice();
    QGeoCoordinate getCoordinate();
    void establishConnection();
    void obtainUserLocation();                                     // only when user hasn't made yet
    void manageConnections();
    Q_INVOKABLE void refreshWeather();
    ~WeatherAPI();
signals:
    void reqSender();
    void locStatusChanged();
    void dataChanged();
public slots:
    void getPlaneCoordinates(const QGeoCoordinate& pos);           // involve every 10 min (main service of plane coordinate)
    void getWeatherData(QNetworkReply* reply);                     // slot for get data
private:
    void setQueryProperties();
    void onClickedButton();
    bool qmlState, gpsObtained;                                    // state which comes from QML (true = PLANE weather, false = USER)
    bool connectionError;
    bool firstReq;
    Connection type;
    QNetworkAccessManager* network;
    QGeoCoordinate coord;
    QGeoPositionInfoSource* src;
    QUrlQuery query;
    QUrl endpoint;
    QNetworkRequest request;
    QTimer* reqTimer;
    WeatherData data;                                              // Storage weather data
};

#endif // WEATHERAPI_H
