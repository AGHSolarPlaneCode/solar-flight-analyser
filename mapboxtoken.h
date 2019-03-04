#ifndef MAPBOXTOKEN_H
#define MAPBOXTOKEN_H

#include <QObject>

class MapboxToken : public QObject
{
    Q_OBJECT
public:
    explicit MapboxToken(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MAPBOXTOKEN_H