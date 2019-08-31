#include "restclientmanager.h"

RESTClientManager::RESTClientManager(QObject* parent): RESTClientInterface(parent),
    _networkManager(new QNetworkAccessManager(this)),
    _requestTimer(new QTimer(this)),
    _requestInterval(10),
    _connectionEstablished(false)
    { setConnections(); }


bool RESTClientManager::establishConnection(const QUrl &endAddress)
{
    _connectionEstablished = false;

    if(_requestTimer->isActive()){
        // AppMessage(MESSAGE::INFORMATION) << ""
        return false;
    }

    if(_endpoint == endAddress){  // the same establishing
        _connectionEstablished = true;
        return true;
    }

    if(!endAddress.isValid())
        return false;

    _endpoint = endAddress;

    _networkRequest.setUrl(_endpoint);

    _connectionEstablished = true;

    return true;
}

void RESTClientManager::runGETRequests()
{
    if(!_connectionEstablished){
        // AppMessage(MESSAGE::INFORMATION) << ""
        return;
    }

    if(!_requestTimer->isActive()){
        _requestTimer->setInterval(static_cast<int>(_requestInterval));

        _requestTimer->start();
    }
}

void RESTClientManager::stopGETRequests()
{
    if(_requestTimer->isActive()){
        _requestTimer->stop();
    }else{
        // AppMessage(MESSAGE::INFORMATION) << "" // info about hasn't started yet ...
    }
}

void RESTClientManager::setRequestsInterval(unsigned int peroid)
{
    if(_requestTimer->isActive()){
        // AppMessage(MESSAGE::INFORMATION) << "" // can't change during timer started
        return;
    }
    if(_requestInterval == peroid)
        return;

    _requestInterval = peroid;
}

QByteArray RESTClientManager::getRESTServerRequest(const QUrl &endpoint)  // static
{
    QNetworkAccessManager tempManager;
    QNetworkRequest networkRequest;
    QByteArray tempArray;

    // add errors handler

    networkRequest.setUrl(endpoint);
    
    connect(&tempManager, &QNetworkAccessManager::finished, [&tempArray](QNetworkReply* reply) -> void { 
        if(QNetworkReply::NoError == reply->error()) //throw error
            return;
        tempArray = reply->readAll();
        
        reply->deleteLater();
    });
    
    tempManager.get(networkRequest);
    
    return tempArray;
}

void RESTClientManager::_requestFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError) { // check kind of errors, and stop connection
         // AppMessage(MESSAGE::INFORMATION) << "" reply->errorString();
        return;
    }
    const auto& telemetryMap = TelemetryJSONManager::parseTelemetryJSONFrame(reply->readAll());
    if(!telemetryMap.isEmpty())
        emit receivedDataTransmitter(telemetryMap);
    else{}
        // AppMessage(MESSAGE::INFORMATION) << "" Empty frame received!

    reply->deleteLater();
}

void RESTClientManager::setConnections()
{
    connect(_networkManager, &QNetworkAccessManager::finished, this, &RESTClientManager::_requestFinished);

    connect(_requestTimer,   &QTimer::timeout, this, [this](){ if(_networkManager) _networkManager->get(_networkRequest); });

    connect(_networkManager, &QNetworkAccessManager::sslErrors, this, &RESTClientManager::_sslErrors);
}

void RESTClientManager::_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors) // FUTURE: user decides about error rejecting
{
    for(const auto& error: errors){
        // AppMessage(MESSAGE::INFORMATION) << "" error.errorString();

        const auto& certificate = error.certificate();
        if(!certificate.isNull()){}
            // AppMessage(MESSAGE::INFORMATION) << "" certificate.toText();
    }

    reply->ignoreSslErrors(errors);
    //reply->deleteLater();  // ? < --
}
