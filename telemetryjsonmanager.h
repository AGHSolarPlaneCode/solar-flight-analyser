#ifndef TELEMETRYJSONMANAGER_H
#define TELEMETRYJSONMANAGER_H

#include <QRandomGenerator>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>
#include <QVariantMap>

namespace Validator{
    QByteArray getRandomTelemetryField();
}

class TelemetryJSONManager
{
public:
    static bool isTelemetryJSONFrame(
            const QByteArray& frame);

    static QVariantMap parseTelemetryJSONFrame(
            const QByteArray& package);
};

#endif // TELEMETRYJSONMANAGER_H
