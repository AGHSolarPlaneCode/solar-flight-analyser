#include "waypointservice.h"

WaypointService::WaypointService(QObject *parent) : QObject(parent)
{

}
void WaypointService::loadFile(QString path){
    path.remove(0,8);
    numberOfPoint = 0;
    QString end = (path.split('.').back());
    Extension extension = Extension::NO_EXTENSION;
    if(end == "csv")
        extension = Extension::CSV;
    else if(end == "txt")
        extension = Extension::TXT;
    else if(end == "waypoints")
        extension = Extension::WAYPOINTS;
    else{
        extension = Extension::NO_EXTENSION;
        RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Unsupported file extension";
        return;
    }
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
          saveToDB(line, extension);
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
void WaypointService::saveToDB(QString line,Extension type){
    if(type == Extension::TXT || type == Extension::WAYPOINTS){
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
    else if(type == Extension::CSV){
        QStringList list = line.split(',');
        if(list.length()>1){
            numberOfPoint++;
            bool isLatValid = false;
            bool isLongValid = false;
            DBLat.push_back(list[0].toDouble(&isLatValid));
            DBLong.push_back(list[1].toDouble(&isLongValid));
            if(!(isLatValid&&isLongValid)){
                clearDB();
                RegisterError(WindowType::MainAppWindow, MessageType::Warning) << "Waypoin file is corrupted";
                throw;

            }
        }
    }
    else
        throw;

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


