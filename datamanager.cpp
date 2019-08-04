#include "datamanager.h"

DataManager::DataManager(QObject *parent) : QObject(parent),
    connectionStatus(std::make_unique<ConnectionSetup>()),
    telemetryInterface(std::make_unique<TelemetrySetup>()) {}

void DataManager::getDataAction()  // START/STOP Button service (base on connection class)
{
    if(!connectionStatus->isRunningConnection()){
        const auto& address(connectionStatus->getURLAddress());

        if(address.isEmpty()) {}
            // TODO: invoke QML JS function with dialog | return
        bool authorizeState = (twoWaysAuthorize.connectionState && twoWaysAuthorize.dataValidation);

        if(!authorizeState)
            return;

        //telemetryInterface->downloadTelemetry(getCurrentEndpoint());

        connectionStatus->setConnectionStatus(true);
    }else{
        //telemetryInterface->stopDownloadTelemetry();

        connectionStatus->setConnectionStatus(false);
    }
}

void DataManager::setCurrentEndpoint(const QUrl &address)
{
    if(connectionStatus->isRunningConnection()){  // check actual position of start button
       // AppMessage(MESSAGE::INFORMATION) << "You cannot change URL address during the START button is launched";
       return;
     }
    // authorization
    if(twoWaysAuthorize.address == address) // the same address (we don't need double authorization)
        return;

    const auto& validConnection = connectionStatus->connectionAvailable(address);

    if(validConnection.first){
        twoWaysAuthorize.connectionState = true;
        if(/*clientManager->telemetryDataAuthorization(validConnection.second)*/true){
            twoWaysAuthorize.dataValidation = true;

            twoWaysAuthorize.address = address;
            connectionStatus->setURLAddress(address);

            emit currentEndpointChanged();
        }else{
            // AppMessage(MESSAGE::INFORMATION) << ""
        }
    }else{
        // AppMessage(MESSAGE::INFORMATION) << ""
    }
}

QUrl DataManager::getCurrentEndpoint() const
{
    return connectionStatus->getURLAddress();
}
