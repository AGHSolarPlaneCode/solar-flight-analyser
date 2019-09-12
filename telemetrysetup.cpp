#include "telemetrysetup.h"

TelemetrySetup::TelemetrySetup(QObject* parent):
    TelemetrySetupInterface(parent),
    telemetryClient(std::make_unique<RESTClientManager>())
{ connect(telemetryClient.get(), &RESTClientManager::receivedDataTransmitter,this,&TelemetrySetup::receiveTelemetryData); }

void TelemetrySetup::setTelemetry(const TelemetryData& data){
    if(telemetry == data)
        return;

    telemetry = data;
}
void TelemetrySetup::resetTelemetry(){

    telemetry = TelemetryData { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };

    qDebug() << telemetry;
}

void TelemetrySetup::setTelemetry(const QVariantMap &fData)
{
    telemetry.Lat         = fData["lat"].toDouble();
    telemetry.Lon         = fData["lon"].toDouble();
    telemetry.latRaw      = fData["latRaw"].toDouble();
    telemetry.lonRaw      = fData["lonRaw"].toDouble();
    telemetry.Alt         = fData["alt"].toDouble();
    telemetry.RelativeAlt = fData["relativeAlt"].toDouble();
    telemetry.Vx          = fData["vx"].toDouble();
    telemetry.Vy          = fData["vy"].toDouble();
    telemetry.Vz          = fData["vz"].toDouble();
    telemetry.Hdg         = fData["hdg"].toDouble();
    telemetry.Row         = fData["row"].toDouble();
    telemetry.Pitch       = fData["pitch"].toDouble();
    telemetry.Yaw         = fData["yaw"].toDouble();
    telemetry.RollSpeed   = fData["rollSpeed"].toDouble();
    telemetry.PitchSpeed  = fData["pitchSpeed"].toDouble();
    telemetry.YawSpeed    = fData["yawSpeed"].toDouble();

    emit telemetryDataReceivedState(true);
}

Data::TelemetryData TelemetrySetup::getTelemetry() const
{
    return telemetry;
}

bool TelemetrySetup::telemetryDataAuthorization(const QByteArray &frame)
{
    if(!TelemetryJSONManager::isTelemetryJSONFrame(frame))
        return false;

    return true;
}

void TelemetrySetup::runTelemetryDownloader(const QUrl &address, bool& runState)  // httpclientmanager service
{
    runState = false;

    if(telemetryClient->establishConnection(address)){

        telemetryClient->runGETRequests();
        runState = true;
    }
}

void TelemetrySetup::stopDownloadTelemetry()
{
    telemetryClient->stopGETRequests();
}

void TelemetrySetup::receiveTelemetryData(const QVariantMap &data)
{
    setTelemetry(data);
}
