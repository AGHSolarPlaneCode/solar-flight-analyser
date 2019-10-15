#ifndef WAYPOINTSERVICE_H
#define WAYPOINTSERVICE_H

#include <QObject>
#include <QGeoCoordinate>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "errorsingleton.h"
#include <QList>

class WaypointService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<double> DBLat READ getDBLat NOTIFY pointsListChanged)
    Q_PROPERTY(QList<double> DBLong READ getDBLong  NOTIFY pointsListChanged)
public:
    explicit WaypointService(QObject *parent = nullptr);
     QList<double> getDBLat();
     QList<double> getDBLong();



signals:
    void pointsListChanged();
public slots:
    void loadFile(QString path);
private:
    void saveToDB(QString line);
    void clearDB();
    QList<double> DBLat;
    QList<double> DBLong;
    int numberOfPoint = 0;
};

#endif // WAYPOINTSERVICE_H
