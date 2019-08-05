#include "telemetrysetup.h"

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
    /*
     if(clientHttpManager->establishConnection(address, )
     clientHttpManager->startGETRequest();

  */
}

void TelemetrySetup::stopDownloadTelemetry()
{
    // httpclientmanager method using to stop telemetry flow
}

void TelemetrySetup::receiveTelemetryData(const Data::TelemetryData &fData)
{
    setTelemetry(fData);
}
