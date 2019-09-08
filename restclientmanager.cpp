#include "restclientmanager.h"

//using namespace REST::Client;
//using namespace REST::ClientAuthorization;

REST::Client::RESTClientManager::RESTClientManager(QObject* parent): RESTClientInterface(parent),
    _networkManager(new QNetworkAccessManager(this)),
    _requestTimer(new QTimer(this)),
    _requestInterval(10),
    _connectionEstablished(false)
    { setConnections(); }


bool REST::Client::RESTClientManager::establishConnection(const QUrl &endAddress)
{
    _connectionEstablished = false;

    if(_requestTimer->isActive()){
        // AppMessage(MESSAGE::INFORMATION) << ""
        _connectionEstablished = true;
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

void REST::Client::RESTClientManager::runGETRequests()
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

void REST::Client::RESTClientManager::stopGETRequests()
{
    if(_requestTimer->isActive()){
        _requestTimer->stop();
    }else{
        // AppMessage(MESSAGE::INFORMATION) << "" // info about hasn't started yet ...
    }
}

void REST::Client::RESTClientManager::setRequestsInterval(unsigned int peroid)
{
    if(_requestTimer->isActive()){
        // AppMessage(MESSAGE::INFORMATION) << "" // can't change during timer started
        return;
    }
    if(_requestInterval == peroid)
        return;

    _requestInterval = peroid;
}

/*
QByteArray REST::Client::RESTClientManager::getRESTServerRequest(const QUrl &endpoint)  // static
{
    static QNetworkAccessManager tempManager;
    //QEventLoop loop;

    QNetworkRequest networkRequest;
    QByteArray tempArray;

    //loop.connect(&tempManager, &QNetworkAccessManager::finished,&loop, &QEventLoop::quit);
    networkRequest.setUrl(endpoint);
    
    connect(&tempManager, &QNetworkAccessManager::finished, [](QNetworkReply* reply) -> void { // http://localhost:8080/currTele
        if(QNetworkReply::NoError != reply->error()){ //throw error
            qDebug()<<reply->errorString();
            return;
        }
        //tempArray = reply->readAll();
        qDebug() <<"JSON: "<< reply->readAll();

        reply->deleteLater();
    });

    tempManager.get(networkRequest);
    //loop.exec();

    return tempArray;
}
*/

void REST::Client::RESTClientManager::_requestFinished(QNetworkReply *reply)
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

void REST::Client::RESTClientManager::setConnections()
{
    connect(_networkManager, &QNetworkAccessManager::finished, this, &RESTClientManager::_requestFinished);

    connect(_requestTimer,   &QTimer::timeout, this, [this](){ if(_networkManager) _networkManager->get(_networkRequest); });

    connect(_networkManager, &QNetworkAccessManager::sslErrors, this, &RESTClientManager::_sslErrors);
}

void REST::Client::RESTClientManager::_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors) // FUTURE: user decides about error rejecting
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


// AUTHORIZATION

std::unique_ptr<QNetworkAccessManager> REST::ClientAuthorization::RESTAuthorizator::authManager = nullptr;
QByteArray REST::ClientAuthorization::RESTAuthorizator::authArray;

REST::ClientAuthorization::RESTAuthorizator::RESTAuthorizator(QObject* parent): QObject(parent) {}

//TEST -> http://localhost:8080/currTele

QByteArray REST::ClientAuthorization::RESTAuthorizator::getRESTServerRequest(const QUrl &endpoint)  // < single request with finished waiting
{
    if(!authManager.get()){
        authManager = std::make_unique<QNetworkAccessManager>();
        connect(authManager.get(), &QNetworkAccessManager::finished, [](QNetworkReply* reply) -> void {
            if(QNetworkReply::NoError != reply->error()){
                qDebug()<<reply->errorString();
                return;
            }
            authArray = reply->readAll();
            reply->deleteLater();
        });
    }

    QEventLoop loop;                                                     // < waiting for lambda finished
    QNetworkRequest networkRequest;
    QByteArray tempArray;
    loop.connect(authManager.get(), &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    networkRequest.setUrl(endpoint);
    authArray.clear();

    if(authManager)
        authManager->get(networkRequest);
    loop.exec();

    return authArray;
}
