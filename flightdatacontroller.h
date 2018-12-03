#ifndef FLIGHTDATACONTROLLER_H
#define FLIGHTDATACONTROLLER_H

#include <QObject>

class FlightDataController : public QObject
{
    Q_OBJECT
public:
    explicit FlightDataController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FLIGHTDATACONTROLLER_H