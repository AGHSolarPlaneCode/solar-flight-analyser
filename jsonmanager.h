#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include "flightdatastruct.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QDebug>
class JSONManager : public QObject
{
    Q_OBJECT
public:
    enum class JSON_STATE{PARSED = 1, UNPARSED = 0};
    enum class GET_STATE{DOWNLOADED = 1, WAITING = 0};
    explicit JSONManager(QObject *parent = nullptr);
    void getJSON(const QByteArray& json) {frame = json;}
    void parseJSON();
    void moveToStruct();
    FlightData getReadyFlightData();
signals:

public slots:
    void ifDownload(bool state);
private:
    GET_STATE get;
    JSON_STATE json_state;
    void resetFrame(){frame.clear();}
    FlightData data;
    QByteArray frame;
};

#endif // JSONMANAGER_H
