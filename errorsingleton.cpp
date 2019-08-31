#include "errorsingleton.h"


std::shared_ptr<ErrorSingleton> ErrorSingleton::error_Handler = nullptr;
QMutex ErrorSingleton::handlerLocker;

// 1. TODO: Priority Queue collection
// 2. TODO: Enum register

void operator<<(ErrorSingleton& debug, const QByteArray& reply){
    #if DEF_DEBUG == 1
        qDebug() << reply;
    #endif

    if(debug.enumTypes.first == WindowType::NoType || debug.enumTypes.second == MessageType::NoType)
        return;

    if(WindowType::MainAppWindow == debug.enumTypes.first){
        if(debug.notifyBellState){
            debug.sendMessageToMainNotification(reply, debug.enumTypes.second);
        }else{
            // add to own container
        }
        
    }else if(WindowType::URLDialogWindow == debug.enumTypes.first){
        // it doesn't depend for notify bell
        debug.sendMessageToDialogWindow(reply, debug.enumTypes.second);
    }else{
        
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
