#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <memory>
#include "connectionsetup.h"
#include "connectionauthorization.h"
#include "telemetrysetup.h"

class DataManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl currentEndpoint READ getCurrentEndpoint WRITE setCurrentEndpoint NOTIFY currentEndpointChanged)
public:
    explicit DataManager(QObject *parent = nullptr);

    Q_INVOKABLE void getDataAction();

    void setCurrentEndpoint(const QUrl& address);
    QUrl getCurrentEndpoint() const;


signals:
    void currentEndpointChanged();

public slots:
private:
    std::unique_ptr<ConnectionInterface>     connectionStatus;
    std::unique_ptr<TelemetrySetupInterface> telemetryInterface;
    Authorization twoWaysAuthorize;

};

#endif // DATAMANAGER_H
