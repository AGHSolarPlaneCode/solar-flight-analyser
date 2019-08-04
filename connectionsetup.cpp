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

QPair<bool, QString> ConnectionSetup::connectionAvailable(const QUrl &qurl)  // return pair (bool, QString)
{
    return QPair<bool, QString>();             // TODO: first way of autorization | using static method of rest client class
}

bool ConnectionSetup::isRunningConnection()
{
    switch(buttonStatus){
    case ConnectButton::START:
        return true;
    case ConnectButton::STOP:
        return false;
    }
}




