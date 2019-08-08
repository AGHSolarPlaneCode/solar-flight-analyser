#include "errorsingleton.h"

std::shared_ptr<ErrorSingleton> ErrorSingleton::error_Handler = nullptr;
QQueue<QByteArray> ErrorSingleton::errorQueue;

void operator<<(ErrorSingleton& debug, const QByteArray& reply){
    #if DEF_DEBUG == 1
        qDebug() << reply;
    #endif
    if(!debug.getNotifyBellState())
        debug.errorQueue.enqueue(reply);

    emit debug.sendMessageToQML(reply);
}
ErrorSingleton &ErrorSingleton::AppWariningRegister()
{
    if(!error_Handler.get())
        error_Handler = std::make_shared<ErrorSingleton>();

    return *error_Handler;
}

void ErrorSingleton::showErrorsQueue()
{
    if(errorQueue.isEmpty()){
        qDebug()<<"Errors Queue is Empty!";
        return;
    }

    for(const auto& error: errorQueue)
        qDebug()<<error;
}

bool ErrorSingleton::getNotifyBellState() const
{
    return notifyBellState;
}

void ErrorSingleton::setNotifyBellState(bool bellState)
{
    if (notifyBellState == bellState)
        return;

    notifyBellState = bellState;
    emit notifyBellStateChanged();
}
