#ifndef TELEMETRYSETUP_H
#define TELEMETRYSETUP_H

#include <memory>
#include "telemetrysetupinterface.h"
#include <restclientmanager.h>

class TelemetrySetup: public TelemetrySetupInterface
{
    Q_OBJECT
public:
    TelemetrySetup(QObject* parent = nullptr);

    void setTelemetry(const TelemetryData& data) override;
    TelemetryData getTelemetry() const override;
    bool telemetryDataAuthorization(const QString& frame) final;
    void downloadTelemetry(const QUrl& address) override;
    void stopDownloadTelemetry() final;
public slots:
    void receiveTelemetryData(const TelemetryData& fData);
private:
    TelemetryData telemetry;
    std::unique_ptr<RESTClientInterface> telemetryClient;
};

#endif // TELEMETRYSETUP_H
