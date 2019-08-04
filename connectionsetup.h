#ifndef CONNECTIONSETUP_H
#define CONNECTIONSETUP_H
#include "connectioninterface.h"

class ConnectionSetup: public ConnectionInterface
{
public:
    enum class ConnectButton{
        START = 1,
        STOP = 0
    };
    ConnectionSetup();

    virtual void setURLAddress(const QUrl& newUrl) override;
    virtual void setConnectionStatus(bool status) override;
    virtual QUrl getURLAddress() const override;
    virtual QPair<bool, QString> connectionAvailable(const QUrl& qurl) override;
    virtual bool isRunningConnection() override;

private:
    QUrl endpointAddress;
    ConnectButton buttonStatus;
};

#endif // CONNECTIONSETUP_H
