#include "routeplanner.h"

RoutePlanner::RoutePlanner(QObject *parent) : QObject(parent), lastPosition(), startPoint()
  ,endPoint()
{}

RoutePlanner::RoutePlanner(const QGeoCoordinate& firstPosition, const QGeoCoordinate& lastPosition, QObject* parent) : QObject(parent),
    startPoint(firstPosition), endPoint(lastPosition) {}

void RoutePlanner::setPoint(const QGeoCoordinate& point){
    if(lastPosition == point)
        return;
    else
        lastPosition = point;
    emit movePosition();
}

