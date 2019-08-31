#ifndef CONNECTIONSETUP_H
#define CONNECTIONSETUP_H
#include "connectioninterface.h"
#include "restclientmanager.h"

class ConnectionSetup: public ConnectionInterface
{
public:
    ConnectionSetup();

    void setURLAddress(const QUrl& newUrl) override;
    void setConnectionStatus(bool status) override;
    bool isRunningConnection() const override;
    QUrl getURLAddress() const override;
    QPair<bool, QByteArray> connectionAvailable(const QUrl& qurl) override;

private:
    QUrl endpointAddress;
    bool _dataFlowButtonState = false;
};

#endif // CONNECTIONSETUP_H
