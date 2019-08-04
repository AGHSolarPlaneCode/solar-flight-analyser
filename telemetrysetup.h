#ifndef TELEMETRYSETUP_H
#define TELEMETRYSETUP_H

#include "telemetrysetupinterface.h"

class TelemetrySetup: public TelemetrySetupInterface
{
    Q_OBJECT
public:
    TelemetrySetup(QObject* parent = nullptr): TelemetrySetupInterface(parent) {}

    virtual void setTelemetry(const TelemetryData& data) final;
    virtual bool telemetryDataAuthorization(const QString& frame) final;
    virtual void downloadTelemetry(const QUrl& address) override;
    virtual void stopDownloadTelemetry() final;
public slots:

private:
    TelemetryData telemetry;

};

#endif // TELEMETRYSETUP_H
