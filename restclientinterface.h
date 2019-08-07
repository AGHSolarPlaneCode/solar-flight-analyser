#ifndef RESTCLIENTINTERFACE_H
#define RESTCLIENTINTERFACE_H

#include <QObject>
#include "telemetrydata.h"

class RESTClientInterface: public QObject{
    Q_OBJECT
public:
    RESTClientInterface(QObject* parent = nullptr): QObject(parent) {}
    virtual bool establishConnection(const QUrl& endAddress) = 0;
    virtual void runGETRequests() = 0;
    virtual void stopGETRequests() = 0;
    virtual void setRequestsInterval(unsigned int peroid) = 0;
signals:
    void receivedDataTransmitter(const QVariantMap& telemetryMap);
};

#endif // RESTCLIENTINTERFACE_H
