#include "waypointservice.h"

WaypointService::WaypointService(QObject *parent) : QObject(parent)
{

}
void WaypointService::loadFile(QString path){
    path.remove(0,8);
    numberOfPoint = 0;
    QFile file(path);
    clearDB();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Failed to load file by path";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        try {
          saveToDB(line);
        }
        catch (...){
        return;
        }
        }
    if(numberOfPoint<1){
        RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Error on file parsing";
        return;
    }
    emit pointsListChanged();
    RegisterError(WindowType::MainAppWindow,MessageType::Information) << "Mission loaded succesfuly!";
}
void WaypointService::saveToDB(QString line){
    QStringList list = line.split("\t");
    if(list.length()>10){
        numberOfPoint++;
        bool isLatValid = false;
        bool isLongValid = false;
        DBLat.push_back(list[8].toDouble(&isLatValid));
        DBLong.push_back(list[9].toDouble(&isLongValid));
        if(!(isLatValid&&isLongValid)){
            clearDB();
            RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Waypoin file is corrupted";
            throw;

        }
    }

}
void WaypointService::clearDB(){
    DBLat.clear();
    DBLong.clear();
}
QList<double> WaypointService::getDBLat(){
    return DBLat;
}
QList<double> WaypointService::getDBLong(){
    return DBLong;
}


