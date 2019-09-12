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

    virtual void setTelemetry(const QVariantMap& data) = 0;
    virtual void setTelemetry(const TelemetryData& data) = 0;
    virtual TelemetryData getTelemetry() const = 0;
    virtual void resetTelemetry() = 0;
    virtual bool telemetryDataAuthorization(const QByteArray& frame) = 0;
    virtual void runTelemetryDownloader(const QUrl& address, bool& runState) = 0;
    virtual void stopDownloadTelemetry() = 0;
    virtual ~TelemetrySetupInterface() = default;
signals:
    void telemetryDataReceivedState(bool state);
};

#endif // TELEMETRYSETUPINTERFACE_H
