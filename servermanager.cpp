#include "servermanager.h"
#include <QThread> //For testing only, remove on implementation

ServerManager::ServerManager(const QUrl& url,QObject *parent) : QObject(parent),
    network(new QNetworkAccessManager(this)), frame(new JSONManager(this)) {
    //- set endpoint request
    setUrl(url);
    setConnections();
}

// 1. setConnections - such as now
// 2. Error of JSON
// Update State- > true -> isRunning() ?
void ServerManager::setConnections(){

    // - connect request with JSONManager method
    QObject::connect(network, SIGNAL(finished(QNetworkReply*)),this, SLOT(getRequestData(QNetworkReply*)));

    // - more than one error handling
    QObject::connect(network, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> &)),
    this, SLOT(handleErrors(QNetworkReply*, const QList<QSslError>&)));

    QObject::connect(frame, &JSONManager::errorSender, this, &ServerManager::getJSONErrors);

    // - send a signal to JSONManager about recived JSON
    QObject::connect(this,SIGNAL(JSONState(bool)), frame, SLOT(ifDownload(bool)));
}

void ServerManager::getJSONErrors(const ErrorManager::JSONErrors& type, const QJsonParseError& e){
    errors.errorJSONValidator(type, e);
}

void ServerManager::setUrl(const QUrl &url)
{
    if(url.isValid()){
        endpoint = url;
        request.setUrl(endpoint);
    }
    else{
        qDebug()<<"Invalid URL address!";
        return;
    }
}

void ServerManager::update(){
    // main public method to get request
    if(network)
        network->get(request);
}

ErrorManager* ServerManager::getErrorManager(){
    return &errors;
}

void ServerManager::getRequestData(QNetworkReply* reply){
    if(QNetworkReply::NetworkError::NoError == reply->error()){
        auto json(reply->readAll());

        frame->parseJSON(json);                                                           // - parsing data

    }else{
        errors.errorRequestValidator(ErrorManager::RequestErrors::REPLY, reply);
    }
    reply->deleteLater();
}

void ServerManager::handleErrors(QNetworkReply* reply, const QList<QSslError>& err){
    errors.errorRequestValidator(ErrorManager::RequestErrors::SSL, reply, err);       // - sending all errors to qml and waiting for reply
}

FlightData ServerManager::getData(){
    emit JSONState(true);                                                             // - data recived
    return frame->getReadyFlightData();
}

