#include "errorsingleton.h"


std::shared_ptr<ErrorSingleton> ErrorSingleton::error_Handler = nullptr;
QMutex ErrorSingleton::handlerLocker;

void operator<<(ErrorSingleton& debug, const QByteArray& reply){
    #if DEF_DEBUG == 1
        qDebug() << reply;
    #endif

    if(debug.enumTypes.first == WindowType::NoType || debug.enumTypes.second == MessageType::NoType)
        return;

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
        case WindowType::NoType:
            qDebug() << "Window type doesn't occured!";
            break;
        default:
            qDebug() << "Undefined window type!";
            break;
    }
}

ErrorSingleton *ErrorSingleton::getInstance()
{
    QMutexLocker locker(&handlerLocker);

    if(!error_Handler.get())
        error_Handler = std::shared_ptr<ErrorSingleton>(new ErrorSingleton());

    error_Handler->enumTypes = qMakePair(WindowType::NoType, MessageType::NoType);

    return error_Handler.get();
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
    if(error_Handler->errorQueue.isEmpty()){
        qDebug()<<"Errors Queue is Empty!";
        return;
    }

    for(const auto& error: error_Handler->errorQueue)
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
