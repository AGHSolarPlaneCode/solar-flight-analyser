#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <QObject>
#include <QGeoCoordinate>

class RoutePlanner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate point READ getPoint WRITE setPoint NOTIFY movePosition)
    Q_PROPERTY(QGeoCoordinate startPoint READ getStartPos)
    Q_PROPERTY(QGeoCoordinate endPoint READ getLastPos)

public:
    RoutePlanner(const QGeoCoordinate& firstPosition = QGeoCoordinate(50.0619474,19.9368564),
    const QGeoCoordinate& lastPosition = QGeoCoordinate(54.347628,18.6452029), QObject* parent = nullptr);
    void setPoint(const QGeoCoordinate& point);
    inline QGeoCoordinate getPoint(){ return lastPosition; }
    inline QGeoCoordinate getStartPos(){return startPoint; }
    inline QGeoCoordinate getLastPos(){return endPoint; }
signals:
    void movePosition();
public slots:

private:
    QGeoCoordinate lastPosition;
    QGeoCoordinate startPoint, endPoint; // add coordinates in constructor
};

#endif // ROUTEPLANNER_H
