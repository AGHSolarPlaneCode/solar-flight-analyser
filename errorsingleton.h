#ifndef ERRORSINGLETON_H
#define ERRORSINGLETON_H

#define DEF_DEBUG 0
#include <QObject>
#include <QDebug>
#include <memory>
#include <QQueue>
#include <QMutexLocker>
#include "notifyenums.h"

class ErrorSingleton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool notifyBellState READ getNotifyBellState WRITE setNotifyBellState NOTIFY notifyBellStateChanged)
public:
    Q_ENUM(WindowType)
    Q_ENUM(MessageType)

    ErrorSingleton(const ErrorSingleton& errSing) = delete;
    ErrorSingleton& operator=(const ErrorSingleton& errSing) = delete;
    static ErrorSingleton* getInstance();
    static ErrorSingleton& AppWariningRegister(const WindowType& wType, const MessageType& mType);
    static void showErrorsQueue();

    void setNotifyBellState(bool bellState);
    bool getNotifyBellState() const;

    friend void operator<<(ErrorSingleton& debug, const QByteArray& reply);
signals:
    void notifyBellStateChanged();
    void sendMessageToMainNotification(const QString& message, MessageType type);
    void sendMessageToDialogWindow(const QString& message);
private:
    explicit ErrorSingleton(QObject *parent = nullptr): QObject(parent) {}

    bool                                   notifyBellState = true;
    static QMutex                          handlerLocker;
    static std::shared_ptr<ErrorSingleton> error_Handler;
    QQueue<QByteArray>                     errorQueue;
    QPair<WindowType, MessageType>         enumTypes;
};

constexpr auto RegisterError = &ErrorSingleton::AppWariningRegister;

#endif // ERRORSINGLETON_H
