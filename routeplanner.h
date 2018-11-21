#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <QObject>
#include <QGeoCoordinate>

class RoutePlanner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate point READ getStartPos WRITE setPoint NOTIFY movePosition)
    Q_PROPERTY(QGeoCoordinate startPoint READ getStartPos)
    Q_PROPERTY(QGeoCoordinate endPoint READ getLastPos)

public:
    explicit RoutePlanner(QObject *parent = nullptr);
    RoutePlanner(const QGeoCoordinate& firstPosition, const QGeoCoordinate& lastPosition, QObject* parent = nullptr);
    void setPoint(const QGeoCoordinate& point);
    inline QGeoCoordinate getPoint(){ return lastPosition; }
    inline QGeoCoordinate getStartPos(){return startPoint; }
    inline QGeoCoordinate getLastPos(){return endPoint; }

signals:
    void movePosition();
public slots:
private:
    QGeoCoordinate lastPosition;
    QGeoCoordinate startPoint, endPoint;
};

#endif // ROUTEPLANNER_H
