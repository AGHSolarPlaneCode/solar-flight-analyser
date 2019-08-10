#include "errorsingleton.h"

std::shared_ptr<ErrorSingleton> ErrorSingleton::error_Handler = nullptr;
QQueue<QByteArray> ErrorSingleton::errorQueue;
QMutex ErrorSingleton::handlerLocker;

void operator<<(ErrorSingleton& debug, const QByteArray& reply){
    #if DEF_DEBUG == 1
        qDebug() << reply;
    #endif
    if(!debug.getNotifyBellState())
        debug.errorQueue.enqueue(reply);

        // error validator
    switch(debug.enumTypes.first){
        case WindowType::MainAppWindow:
            emit debug.sendMessageToMainNotification(reply, debug.enumTypes.second);
            break;
        case WindowType::URLDialogWindow:
            emit debug.sendMessageToDialogWindow(reply);
            break;
        default:
            emit debug.sendMessageToMainNotification(reply, MessageType::UNDEFINED);
            break;
    }
}
ErrorSingleton &ErrorSingleton::AppWariningRegister(const WindowType& winType, const MessageType& messType)
{
    QMutexLocker locker(&handlerLocker);

    if(!error_Handler.get())
        error_Handler = std::shared_ptr<ErrorSingleton>(new ErrorSingleton());

    error_Handler->enumTypes = qMakePair(winType, messType);

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
    // reaction for turning on

    notifyBellState = bellState;
    emit notifyBellStateChanged();
}
