#include "errorhandler.h"

int ErrorHandler::errorCtr = 0;

JsonError::JsonError(Errors state, const QJsonParseError& err,QObject *parent): QObject(parent),
    type(state), error(err) {}

JsonError::JsonError(const JsonError& err): type(err.type), error(err.error), QObject(nullptr) {}

void JsonError::showErrorMessage() const{
    qDebug()<< error.errorString();             // - if we don't have any error, message is default
}

void JsonError::showErrorMessage(const QString& message) const{
    qDebug()<< message;
}

QString JsonError::getErrorMessage() const{
    return error.errorString();
}

JsonError& JsonError::operator=(JsonError&& err){
    if(this == &err )
        return *this;

    this->error = err.error;
    err.error = QJsonParseError();
    this->type = err.type;
    err.type = Errors::DEFAULT;

    return *this;
}
void JsonError::errorValidator() const{
    switch(type){
    case Errors::JSON:{
        showErrorMessage();
        auto jsonErrorMessage(getErrorMessage());
        emit sendToFrontend(jsonErrorMessage);
    } break;

    case Errors::EMPTY:{
        QString empty("Empty frame!");
        showErrorMessage(empty);
        emit sendToFrontend(empty);
    }break;

    default:
        showErrorMessage();     // - no error occured
        break;

    }
}
