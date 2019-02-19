#include "servermanager.h"
#include <QThread> //For testing only, remove on implementation

ServerManager::ServerManager(const QUrl& url,QObject *parent) : QObject(parent),
    network(new QNetworkAccessManager(this)), endpoint(url), request(), frame(new JSONManager(this)) {
    //- set endpoint request
    request.setUrl(endpoint);
    setConnections();
    mode = State::STOP;
}

void ServerManager::setConnections(){

    // - connect request with JSONManager method
    QObject::connect(network, SIGNAL(finished(QNetworkReply*)),this, SLOT(getRequestData(QNetworkReply*)));

    // - more than one error handling
    QObject::connect(network, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> &)),
    this, SLOT(handleErrors(QNetworkReply*, const QList<QSslError>&)));

    // - send a signal to JSONManager about recived JSON
    QObject::connect(this,SIGNAL(JSONState(bool)), frame, SLOT(ifDownload(bool)));
}

void ServerManager::setUrl(const QUrl &url)
{
    endpoint = url;
}

void ServerManager::HttpGETRequest(){
    network->get(request); // use ERROR
}

void ServerManager::Update(){
    if(State::STOP == mode)
        mode = State::RUN;
    // QThread::msleep(30); test
    HttpGETRequest();
}

void ServerManager::getRequestData(QNetworkReply* reply){
    try{
        if(QNetworkReply::NetworkError::NoError == reply->error()){
            auto json(reply->readAll());

            frame->getJSON(json);
            frame->parseJSON();      // - parsing data
        }else{
            // - request throw
        }
    }
    catch(const JsonError& e){
        e.errorValidator();
    }
    reply->deleteLater();
}

void ServerManager::handleErrors(QNetworkReply* reply, const QList<QSslError>& errors){
    qDebug()<<"MORE THAN ONE ERROR";
    /*

        // ... errors analysis (more than one)  -> class

    */
}

FlightData ServerManager::getData(){
    emit JSONState(true); // data recived
    return frame->getReadyFlightData();
}

