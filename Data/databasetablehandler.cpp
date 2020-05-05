#include "databasetablehandler.h"
#include <QVariant>
#include <iostream>

namespace Data{
    void DatabaseTableHandler::fetchColumns(){
        unsigned table_count = database->tableExists(tableName);
        if(table_count < 1)
            throw std::ios_base::failure("Requested table with name " + tableName.toStdString() + ", which doesn't exist.");
        columnNames = database->getTableColumns(this->tableName);
    }

    DatabaseTableHandler::DatabaseTableHandler(DatabaseConnection * db, const QString & tableName)
    {
        this->database = db;
        this->tableName = tableName;
        fetchColumns();
    }

    QString DatabaseTableHandler::getNameOfColumn(unsigned columnId){
        return columnNames.at(columnId).first;
    }

    void DatabaseTableHandler::setValueByKey(const QString & key, const QString & column, const QString & value, int key_idx){
        QString keyName;
        for(auto it = columnNames.begin(); it != columnNames.end(); it++){
            if(it->second != false){
                if(--key_idx < 0){
                    keyName = it->first;
                    break;
                }
            }
        }

        QString keySelector = QString("%1='%2'").arg(keyName).arg(key);


        database->updateRecord(tableName, keySelector, QString("%1='%2'").arg(column).arg(value));
    }

}
