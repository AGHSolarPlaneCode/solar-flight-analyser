#ifndef CONNECTIONSETUP_H
#define CONNECTIONSETUP_H
#include "connectioninterface.h"
#include "restclientmanager.h"

class ConnectionSetup: public ConnectionInterface
{
public:
    enum class ConnectButton{
        START = 1,
        STOP = 0
    };
    ConnectionSetup();

    void setURLAddress(const QUrl& newUrl) override;
    void setConnectionStatus(bool status) override;
    QUrl getURLAddress() const override;
    QPair<bool, QString> connectionAvailable(const QUrl& qurl) override;
    bool isRunningConnection() override;

private:
    QUrl endpointAddress;
    ConnectButton buttonStatus;
};

#endif // CONNECTIONSETUP_H
