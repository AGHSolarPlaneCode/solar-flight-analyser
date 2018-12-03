#ifndef FLIGHTDATAADAPTER_H
#define FLIGHTDATAADAPTER_H

#include <QObject>

class FlightDataAdapter : public QObject
{
    Q_OBJECT
public:
    explicit FlightDataAdapter(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FLIGHTDATAADAPTER_H