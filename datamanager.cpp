#include "datamanager.h"

DataManager::DataManager(QObject *parent) : QObject(parent),
    connectionStatus(std::make_unique<ConnectionSetup>()),
    telemetryInterface(std::make_unique<TelemetrySetup>())
{ connect(telemetryInterface.get(), &TelemetrySetup::telemetryDataReceivedState, this, &DataManager::telemetryDataState); }

void DataManager::getDataAction()  // START/STOP Button service (base on connection class)
{
    if(!connectionStatus->isRunningConnection()){
        const auto& address(connectionStatus->getURLAddress());

        if(address.isEmpty()) {}
            // TODO: invoke QML JS function with dialog | return
        bool authorizeState = (twoWaysAuthorize.connectionState && twoWaysAuthorize.dataValidation);

        if(!authorizeState){  // error message | information
            // AppMessage(MESSAGE::INFORMATION) << "" invalid address
            return;
        }

        telemetryInterface->downloadTelemetry(getCurrentEndpoint());

        connectionStatus->setConnectionStatus(true);  // button state - to changed encapsulation
    }else{
        telemetryInterface->stopDownloadTelemetry();

        connectionStatus->setConnectionStatus(false);
    }
}

void DataManager::setCurrentEndpoint(const QUrl &address)
{
    if(connectionStatus->isRunningConnection()){  // check actual position of start button
       // AppMessage(MESSAGE::INFORMATION) << "You cannot change URL address during the START button is launched";
       return;
     }

    if(!address.isValid()){
        // AppMessage(MESSAGE::INFORMATION) << "" invalid address
        return;
    }

    // authorization
    if(twoWaysAuthorize.address == address) // the same address (we don't need double authorization)
        return;

    const auto& validConnection = connectionStatus->connectionAvailable(address);    // first step

    if(validConnection.first){
        twoWaysAuthorize.connectionState = true;
        if(telemetryInterface->telemetryDataAuthorization(validConnection.second)){  // second step
            twoWaysAuthorize.dataValidation = true;

            twoWaysAuthorize.address = address;
            connectionStatus->setURLAddress(address);

            emit currentEndpointChanged();
        }else{
            twoWaysAuthorize.dataValidation = false;
            // AppMessage(MESSAGE::INFORMATION) << ""
        }
    }else{
        twoWaysAuthorize.connectionState = false;
        // AppMessage(MESSAGE::INFORMATION) << ""
    }
}

void DataManager::telemetryDataState(bool state)
{
    if(!state){
        // AppMessage(MESSAGE::INFORMATION) << ""
        return;
    }

    emit telemetryDataChanged();
}

QUrl DataManager::getCurrentEndpoint() const
{
    return connectionStatus->getURLAddress();
}

double DataManager::getLat() const
{
    return telemetryInterface->getTelemetry().Lat;
}

double DataManager::getLon() const
{
    return telemetryInterface->getTelemetry().Lon;
}

double DataManager::getLatRaw() const
{
    return telemetryInterface->getTelemetry().latRaw;
}

double DataManager::getLonRaw() const
{
    return telemetryInterface->getTelemetry().lonRaw;
}

double DataManager::getAlt() const
{
    return telemetryInterface->getTelemetry().Alt;
}

double DataManager::getRelativeAlt() const
{
    return telemetryInterface->getTelemetry().RelativeAlt;
}

double DataManager::getVx() const
{
    return telemetryInterface->getTelemetry().Vx;
}

double DataManager::getVy() const
{
    return telemetryInterface->getTelemetry().Vy;
}

double DataManager::getVz() const
{
    return telemetryInterface->getTelemetry().Vz;
}

double DataManager::getHdg() const
{
    return telemetryInterface->getTelemetry().Hdg;
}

double DataManager::getRow() const
{
    return telemetryInterface->getTelemetry().Row;
}

double DataManager::getPitch() const
{
    return telemetryInterface->getTelemetry().Pitch;
}

double DataManager::getYaw() const
{
    return telemetryInterface->getTelemetry().Yaw;
}

double DataManager::getRollSpeed() const
{
    return telemetryInterface->getTelemetry().RollSpeed;
}

double DataManager::getPitchSpeed() const
{
    return telemetryInterface->getTelemetry().PitchSpeed;
}

double DataManager::getYawSpeed() const
{
    return telemetryInterface->getTelemetry().YawSpeed;
}

