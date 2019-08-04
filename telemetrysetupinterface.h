#ifndef TELEMETRYSETUPINTERFACE_H
#define TELEMETRYSETUPINTERFACE_H

#include "telemetrydata.h"
#include <QString>
#include <QObject>

using Data::TelemetryData;

class TelemetrySetupInterface: public QObject{
    Q_OBJECT
public:
    TelemetrySetupInterface(QObject* parent = nullptr): QObject(parent) {}

    virtual void setTelemetry(const TelemetryData& data) = 0;
    virtual bool telemetryDataAuthorization(const QString& frame) = 0;
    virtual void downloadTelemetry(const QUrl& address) = 0;
    virtual void stopDownloadTelemetry() = 0;
};

#endif // TELEMETRYSETUPINTERFACE_H
