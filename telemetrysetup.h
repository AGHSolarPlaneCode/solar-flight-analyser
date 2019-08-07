#ifndef TELEMETRYSETUP_H
#define TELEMETRYSETUP_H

#include <memory>
#include "telemetrysetupinterface.h"
#include "restclientmanager.h"
#include "telemetryjsonmanager.h"

class TelemetrySetup: public TelemetrySetupInterface
{
    Q_OBJECT
public:
    TelemetrySetup(QObject* parent = nullptr);

    void setTelemetry(const QVariantMap& data) override;
    void setTelemetry(const TelemetryData& data) override;
    TelemetryData getTelemetry() const override;
    bool telemetryDataAuthorization(const QByteArray& frame) override;
    void downloadTelemetry(const QUrl& address) override;
    void stopDownloadTelemetry() override;
public slots:
    void receiveTelemetryData(const QVariantMap& recData);
private:
    TelemetryData telemetry;
    std::unique_ptr<RESTClientInterface> telemetryClient;
};

#endif // TELEMETRYSETUP_H