#ifndef ERRORSINGLETON_H
#define ERRORSINGLETON_H

#define DEF_DEBUG 0
#include <QObject>
#include <QDebug>
#include <memory>
#include <QQueue>

class ErrorSingleton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool notifyBellState READ getNotifyBellState WRITE setNotifyBellState NOTIFY notifyBellStateChanged)
public:
    enum class WindowType{
        MainAppWindow = 1,
        URLDialogWindow
    };

    enum class MessageType{
        WARINING = 1,
        INFORMATION,
        UNDEFINED
    };

    Q_ENUM(WindowType)
    Q_ENUM(MessageType)

    ErrorSingleton(const ErrorSingleton& errSing) = delete;
    ErrorSingleton& operator=(const ErrorSingleton& errSing) = delete;   
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
    bool   notifyBellState = true;
    static std::shared_ptr<ErrorSingleton> error_Handler;
    static QQueue<QByteArray> errorQueue;
    static QPair<WindowType, MessageType> enumTypes;
};

using MessageType = ErrorSingleton::MessageType;
using WindowType = ErrorSingleton::WindowType;
constexpr auto RegisterError = &ErrorSingleton::AppWariningRegister;

#endif // ERRORSINGLETON_H
