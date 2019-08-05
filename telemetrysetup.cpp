#include "telemetrysetup.h"

TelemetrySetup::TelemetrySetup(QObject* parent): TelemetrySetupInterface(parent),
    telemetryClient(std::make_unique<RESTClientManager>()) {}

void TelemetrySetup::setTelemetry(const Data::TelemetryData &data)
{
    //if(telemetry == data) return;
    //telemetry = data;

    emit telemetryDataReceivedState(true);
}

Data::TelemetryData TelemetrySetup::getTelemetry() const
{
    return telemetry;
}

bool TelemetrySetup::telemetryDataAuthorization(const QString &frame)
{
    return true;
}

void TelemetrySetup::downloadTelemetry(const QUrl &address)  //httpclientmanager service
{
    if(telemetryClient->establishConnection(address))
        telemetryClient->runGETRequests();
}

void TelemetrySetup::stopDownloadTelemetry()
{
    telemetryClient->stopGETRequests();
}

void TelemetrySetup::receiveTelemetryData(const Data::TelemetryData &fData)
{
    setTelemetry(fData);
}
