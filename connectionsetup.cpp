#include "connectionsetup.h"

ConnectionSetup::ConnectionSetup() {}

void ConnectionSetup::setConnectionStatus(bool status)
{   
    if(_dataFlowButtonState == status)
        return;

    _dataFlowButtonState = status;
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
    using namespace REST::ClientAuthorization;
    QByteArray rawFrame = RESTAuthorizator::getRESTServerRequest(qurl);   // single request to check connection

    if(rawFrame.isEmpty())
        return qMakePair<bool, QByteArray>(false, rawFrame);
    else
        return qMakePair<bool, QByteArray>(true, rawFrame);
}

bool ConnectionSetup::isRunningConnection() const
{
    return _dataFlowButtonState;    // < true - is running
}




