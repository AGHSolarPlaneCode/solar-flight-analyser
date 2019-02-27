#include "errorhandler.h"

int ErrorHandler::errorCtr = 0;

ErrorManager::ErrorManager(JSONErrors state, RequestErrors req, const QJsonParseError& err,QNetworkReply* reply, QObject *parent): QObject(parent),
    JStype(state), reType(req), error(err), rpl(reply) {}



void ErrorManager::showErrorMessage() const{
    qDebug()<< error.errorString();                                                    // - if we don't have any error, message is default
}

void ErrorManager::showErrorMessage(const QString& message) const{
    qDebug()<< message;
}

QString ErrorManager::getErrorMessage() const{
    return error.errorString();
}

void ErrorManager::setJsonParseError(const QJsonParseError& e){
    if(&e == &error)
        return;
    error = e;
}

void ErrorManager::errorJSONValidator(const ErrorManager::JSONErrors& t, const QJsonParseError& e){
    JStype = t;

    switch(JStype){
    case JSONErrors::JSON:{
        errorCtr++;
        setJsonParseError(e);
        showErrorMessage();
        auto ErrorManagerMessage(getErrorMessage());
        emit sendJSONErrors(ErrorManagerMessage);
    } break;

    case JSONErrors::EMPTY:{
        errorCtr++;
        QString empty("Empty frame!");
        showErrorMessage(empty);
        emit sendJSONErrors(empty);
    }break;

    default:
        showErrorMessage();     // - no error occured
        break;

    }
}

//--- REQUEST

void ErrorManager::ignoreRequestErrors(){
    if(!sslList.isEmpty() && rpl)
        rpl->ignoreSslErrors(sslList);                                                 // - involve in QML
    else
        return;
}

QVector<QString> ErrorManager::listConverter(){
    QVector<QString> vector;

    if(!sslList.empty()){
        for(auto l: sslList){
             vector.push_back(l.errorString());
        }
      }
    return vector;
}

void ErrorManager::errorRequestValidator(RequestErrors type, QNetworkReply* reply, const QList<QSslError>& list){
    reType = type;

    switch(type){
        case RequestErrors::REPLY:{
            rpl = reply;
            emit sendRequestError(rpl->errorString());
            } break;

        case RequestErrors::SSL:{
            rpl = reply;
            sslList = list;                                                              // - copy list of sslErrors to own sslList

            auto datas(this->listConverter());
            if(!datas.isEmpty())
                emit sendSslVector(datas);
            } break;

        default:
            showErrorMessage();
            break;
    }
}
