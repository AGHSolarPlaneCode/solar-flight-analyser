#include "connectionsetup.h"

ConnectionSetup::ConnectionSetup(): buttonStatus(ConnectButton::STOP) {}

void ConnectionSetup::setConnectionStatus(bool status)
{
    if(status)
        buttonStatus = ConnectButton::START;
    else
        buttonStatus = ConnectButton::STOP;
}

QUrl ConnectionSetup::getURLAddress() const
{
    return endpointAddress;
}

void ConnectionSetup::setURLAddress(const QUrl &newUrl)
{
    if(!newUrl.isValid() || newUrl == endpointAddress)
        return;

    endpointAddress = newUrl;
}

QPair<bool, QByteArray> ConnectionSetup::connectionAvailable(const QUrl &qurl) // return pair (bool <- connection available, QString <- received data)
{
    QByteArray rawFrame = RESTClientManager::getRESTServerRequest(qurl);    // single request to check connection
        
    if(rawFrame.isEmpty())
        return qMakePair<bool, QByteArray>(false, rawFrame);
    else
        return qMakePair<bool, QByteArray>(true, rawFrame);
}

bool ConnectionSetup::isRunningConnection()
{
    if(ConnectButton::START != buttonStatus)
        return false;

    return true;
}



