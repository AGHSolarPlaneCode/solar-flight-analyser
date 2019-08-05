#include "restclientmanager.h"

RESTClientManager::RESTClientManager(QObject* parent): RESTClientInterface(parent),
    _networkManager(new QNetworkAccessManager(this)),
    _requestTimer(new QTimer(this)),
    _requestInterval(10),
    _connectionEstablished(false)
    {}


bool RESTClientManager::establishConnection(const QUrl &endAddress)
{
    if(!endAddress.isValid())
        return false;

    if(_endpoint == endAddress)  // the same establishing
        return true;

    _connectionEstablished = false;

    _endpoint = endAddress;

    _networkRequest.setUrl(_endpoint);

    setConnections();

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
    if(_requestInterval == peroid)
        return;

    if(_requestTimer->isActive()){
        // AppMessage(MESSAGE::INFORMATION) << "" // can't change during timer started
        return;
    }

    _requestInterval = peroid;
}

void RESTClientManager::_requestFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError) {
         // AppMessage(MESSAGE::INFORMATION) << "" reply->errorString();
        return;
    }

    // TODO: parse
    //emit receivedDataTransmitter()
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
}
