#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>
#include <flightdatastruct.h>

class ServerManager : public QObject
{
    Q_OBJECT
public:
    explicit ServerManager(QObject *parent = nullptr);
    void Update();
    FlightData GetData();

signals:

public slots:

public:
    FlightData data;
};

#endif // SERVERMANAGER_H
