#ifndef WEATHERAPI_H
#define WEATHERAPI_H

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
#include <functional>

/* Monday | Tuesday plan */
// 1. Class for data (setters, getters)
// 2. Parsing JSON (slot) -> getWeatherData

// use gpsObtained to check number of involving "getData" slot
// !- to set interval -!

class WeatherAPI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool locStatus READ getLocStatus WRITE setLocStatus NOTIFY locStatusChanged)
public:

    enum class Connection{USER = 1, PLANE, DEFAULT};               // USER - obtain user location of device   PLANE - get location of plane, from DataAdapter
    explicit WeatherAPI(QObject *parent = nullptr);
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
signals:
    void reqSender();
    void locStatusChanged();
public slots:
    void getPlaneCoordinates(const QGeoCoordinate& pos);           // involve every 10 min (main service of plane coordinate)
    void getWeatherData(QNetworkReply* reply);                     // slot for get data
private:
    void setQueryProperties();

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
};

#endif // WEATHERAPI_H
