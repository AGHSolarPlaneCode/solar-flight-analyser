#include "telemetryjsonmanager.h"
#include <QDebug>

namespace Validator{
    QByteArray getRandomTelemetryField(){
    std::uniform_int_distribution<int> rangeGen(1,8);

    int randomVal = rangeGen(*QRandomGenerator::global());

    switch(randomVal){
        case 1:
            return QByteArray("lat");
        case 2:
            return QByteArray("lon");
        case 3:
            return QByteArray("latRaw");
        case 4:
            return QByteArray("lonRaw");
        case 5:
            return QByteArray("alt");
        case 6:
            return QByteArray("relativeAlt");
        case 7:
            return QByteArray("vx");
        case 8:
            return QByteArray("vy");
        case 9:
            return QByteArray("vz");
        default:
            return QByteArray("");
        }
    }
}

bool TelemetryJSONManager::isTelemetryJSONFrame(const QByteArray& frame){
    using Validator::getRandomTelemetryField;

    QJsonDocument responseJson = QJsonDocument::fromJson(frame);
    if(responseJson.isEmpty())
        return false;

    QJsonObject object = responseJson.object();

    if(!object.contains(getRandomTelemetryField()))
        return false;

    return true;
}

QVariantMap TelemetryJSONManager::parseTelemetryJSONFrame(const QByteArray& package){
    QJsonParseError jerror;

    qDebug() << package;

    QJsonDocument responseJson = QJsonDocument::fromJson(package, &jerror);

    if(QJsonParseError::NoError != jerror.errorString()){
        // AppMessage(MESSAGE::INFORMATION) << ""
    }

    QJsonObject obj = responseJson.object();

    return obj.toVariantMap();  // return parsed data QMap of Variants
}
