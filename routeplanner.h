#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <QObject>

class RoutePlanner : public QObject
{
    Q_OBJECT
public:
    explicit RoutePlanner(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ROUTEPLANNER_H