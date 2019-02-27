#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include "flightdatastruct.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QDebug>
#include "errorhandler.h"

class JSONManager : public QObject
{
    Q_OBJECT
public:
    enum class JSON_STATE{PARSED = 1, UNPARSED = 0};
    enum class GET_STATE{DOWNLOADED = 1, WAITING = 0};
    explicit JSONManager(QObject *parent = nullptr);
    void setJSON(const QByteArray& json);
    void parseJSON();
    void moveToStruct();
    void setFlightData(const QJsonObject& obj);
    FlightData getReadyFlightData();
signals:
    void errorSender(const ErrorManager::JSONErrors& t, const QJsonParseError& e = QJsonParseError());
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
