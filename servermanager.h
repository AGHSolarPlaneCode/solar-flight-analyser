 #ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>
#include "flightdatastruct.h"
#include "jsonmanager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkReply>
#include <QDebug>
#include <QSsl>

class ServerManager : public QObject
{
    Q_OBJECT
public:
    enum class State {STOP = 0, RUN, ERROR};
    explicit ServerManager(const QUrl& url, QObject *parent = nullptr);
    void Update();
    void HttpGETRequest();
    inline QUrl getUrl() { return endpoint; }
    FlightData getData();
    void setConnections();
    void setUrl(const QUrl& url);
    //void flightDataReset();
signals:
    void JSONState(bool state);
public slots:
    void handleErrors(QNetworkReply* reply, const QList<QSslError>& errors);
    void getRequestData(QNetworkReply* reply);
private:
    State mode;
    JSONManager* frame;
    QNetworkAccessManager* network;
    QUrl endpoint;
    QNetworkRequest request;
};

#endif // SERVERMANAGER_H
