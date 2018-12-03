#ifndef FLIGHTDATAWORKER_H
#define FLIGHTDATAWORKER_H

#include <QObject>

class FlightDataWorker : public QObject
{
    Q_OBJECT
public:
    explicit FlightDataWorker(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FLIGHTDATAWORKER_H