#include "datamanager.h"

DataManager::DataManager(QObject *parent) : QObject(parent),
    connectionStatus(std::make_unique<ConnectionSetup>()),
    telemetryInterface(std::make_unique<TelemetrySetup>())
{ connect(telemetryInterface.get(), &TelemetrySetup::telemetryDataReceivedState, this, &DataManager::telemetryDataState);
    QTimer::singleShot(3000, [](){

        RegisterError(WindowType::MainAppWindow, MessageType::Information) << "Enter URL address";
        RegisterError(WindowType::MainAppWindow, MessageType::Information) << "Enjoy this app!";

    });
}

void DataManager::getDataAction()                       // START/STOP Button service
{
    if(!connectionStatus->isRunningConnection()){
        const auto& address(connectionStatus->getURLAddress());

        if(address.isEmpty()) {
            emit showDialogAddressWindow();
            return;
        }
                                                        // TODO: button to clear URL address < - valid

        bool authorizeState = (twoWaysAuthorize.connectionState && twoWaysAuthorize.dataValidation);

        if(!authorizeState){
            RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Invalid authorization";
            return;
        }

        bool stableRun;
        telemetryInterface->runTelemetryDownloader(address, stableRun);

        emit activeDataFlowButton(stableRun);           // base on stable run we decide about right data flow

        connectionStatus->setConnectionStatus(stableRun);

    }else{
         telemetryInterface->stopDownloadTelemetry();    // stop data flow, based on current URL address

         emit activeDataFlowButton(false);               // notify frontend
         connectionStatus->setConnectionStatus(false);   // set backend option
    }
}

bool DataManager::getCurrentAuthorizationStatus() const{
    if(twoWaysAuthorize.address.isEmpty())
        return false;

    if(!twoWaysAuthorize.connectionState || !twoWaysAuthorize.dataValidation)
        return false;

    return true;
}

void DataManager::setCurrentEndpoint(const QUrl &address)
{
    if(connectionStatus->isRunningConnection()){  // check actual position of start button
       RegisterError(WindowType::URLDialogWindow, MessageType::Information) << "You cannot change URL address during the START button is launched";
       return;
     }

    if(!address.isValid()){
        qDebug()<<"Address received: " << address.toString();
        RegisterError(WindowType::URLDialogWindow, MessageType::Warning) <<"Invalid address";
        return;
    }

    // authorization
    bool authState = (twoWaysAuthorize.address == address &&
                      twoWaysAuthorize.connectionState &&
                      twoWaysAuthorize.dataValidation);

//    if(twoWaysAuthorize.address == address){
//        if(twoWaysAuthorize.connectionState && twoWaysAuthorize.dataValidation){
//            RegisterError(WindowType::URLDialogWindow, MessageType::Information) << "Address authorization has already done.";
//            return;
//        }
//        else{
//            RegisterError(WindowType::URLDialogWindow, MessageType::Information) << "Address authorization has already denied.";
//            return;
//        }
//    }

    if(authState){ // the same address (we don't need double authorization)
        RegisterError(WindowType::URLDialogWindow, MessageType::Information) << "Address authorization has already done";
        return;
    }

    const auto& validConnection = connectionStatus->connectionAvailable(address);    // first step

    if(!validConnection.first){
        twoWaysAuthorize.connectionState = false;
        twoWaysAuthorize.dataValidation = false;
        twoWaysAuthorize.address = address;
        RegisterError(WindowType::URLDialogWindow, MessageType::Warning) << "Connection authorization denied.";
        return;
    }

    twoWaysAuthorize.connectionState = true;

    if(!telemetryInterface->telemetryDataAuthorization(validConnection.second)){
        twoWaysAuthorize.dataValidation = false;
        twoWaysAuthorize.address = address;
        RegisterError(WindowType::URLDialogWindow, MessageType::Warning) << "Telemetry authorization denied.";
        return;
    }

    twoWaysAuthorize.dataValidation = true;
    twoWaysAuthorize.address = address;
    connectionStatus->setURLAddress(address);

    RegisterError(WindowType::URLDialogWindow, MessageType::Success) << "Authorization Success!";

    emit connectionDataChanged();
}

void DataManager::resetTelemetryData(){
    telemetryInterface->resetTelemetry();

    emit telemetryDataChanged();
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

double DataManager::getGndSpeed() const
{
    return telemetryInterface->getTelemetry().gndSpeed;
}

double DataManager::getBatteryCap() const
{
    return telemetryInterface->getTelemetry().batteryCap;
}
