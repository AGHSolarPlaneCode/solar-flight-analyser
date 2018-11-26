#include "routeplanner.h"


RoutePlanner::RoutePlanner(const QGeoCoordinate& firstPosition, const QGeoCoordinate& lastPosition, QObject* parent) : QObject(parent),
    startPoint(firstPosition), endPoint(lastPosition), lastPosition(firstPosition) {}

void RoutePlanner::setPoint(const QGeoCoordinate& point){
    if(lastPosition == point)
        return;
    else
        lastPosition = point;
    emit movePosition();
}

