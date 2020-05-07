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

    QString DatabaseTableHandler::getFirstKeyName(int key_idx){
        QString keyName;
        for(auto it = columnNames.begin(); it != columnNames.end(); it++){
            if(it->second != false){
                if(--key_idx < 0){
                    keyName = it->first;
                    break;
                }
            }
        }
        return keyName;
    }

    QString DatabaseTableHandler::getKeySelector(const QString &keyValue, int key_idx)
    {
        QString keyName = getFirstKeyName(key_idx);

        return QString("%1='%2'").arg(keyName).arg(keyValue);
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
        QString keyName = getFirstKeyName(key_idx);

        if(!keyExists(keyName, key))
            createByKey(keyName, key);

        QString keySelector = getKeySelector(key, key_idx);


        database->updateRecord(tableName, keySelector, QString("%1='%2'").arg(column).arg(value));
    }


    void DatabaseTableHandler::setValuesByKey(const QString &key, const std::initializer_list<QString> & columns, const std::initializer_list<QString> & values, int key_idx)
    {
        QString keyName =getFirstKeyName(key_idx);

        QString keySelector = QString("%1='%2'").arg(keyName).arg(key);

        QString recordModifier;

        if(!keyExists(keyName, key))
            createByKey(keyName, key);

        for(auto [itC, itV] = std::tuple{columns.begin(), values.begin()}; itC != columns.end() and itV != values.end(); itC++, itV++){
            recordModifier += QString("%1='%2',").arg(*itC).arg(*itV);
        }

        if(recordModifier != "")
            recordModifier.chop(1);

        database->updateRecord(tableName, keySelector, recordModifier);
    }

    QVariant DatabaseTableHandler::getValueFromRow(const QString &key, const QString &columnName, int key_idx)
    {
        QString keyName = getFirstKeyName(key_idx);

        QString keySelector = getKeySelector(key, key_idx);

        if(!keyExists(keyName, key))
            return QVariant(QString(""));
        else{
            return database->getRecord(tableName, keySelector, columnName).at(0);
        }
    }

    bool DatabaseTableHandler::keyExists(const QString &keyName, const QString &keyValue){
        return database->recordExists(tableName, QString("%1='%2'").arg(keyName).arg(keyValue));
    }

    bool DatabaseTableHandler::keyExists(const QString &keyValue, int key_idx)
    {
        return database->recordExists(
                    tableName,
                    QString("%1='%2'").arg(
                        getFirstKeyName(key_idx)
                        ).arg(keyValue)
                    );
    }

    void DatabaseTableHandler::createByKey(const QString &keyName, const QString &keyValue){
        database->createRecord(tableName, keyName, keyValue);
    }

    bool DatabaseTableHandler::createRecord(const std::initializer_list<QString> &columns, const std::initializer_list<QString> &values){
        if(columns.size()) return false;
        if(keyExists(*columns.begin(), *values.begin()))
            return false;
        else{
            QString colnames;
            QString vnames;
            for(auto [itC, itV] = std::tuple{columns.begin(), values.begin()}; itC != columns.end() and itV != values.end(); itC++, itV++){
                colnames.append(QString("%1,").arg(*itC));
                vnames.append(QString("%1,").arg(*itV));
            }
            colnames.chop(1);
            vnames.chop(1);
            database->createRecord(tableName, colnames, vnames);
            return true;
        }
    }

    bool DatabaseTableHandler::createRecord(const std::initializer_list<QString> &values)
    {
        if(values.size()) return false;
        std::vector<QString> columns;
        for(int i = 0; i < columnNames.size() and i < (int)values.size(); i++){
            columns.push_back(columnNames.at(i).first);
        }

        if(keyExists(columns.at(0), *values.begin())) return false;
        else{
            QString colnames;
            QString vnames;

            for(auto [itC, itV] = std::tuple{columns.begin(), values.begin()}; itC != columns.end() and itV != values.end(); itC++, itV++){
                colnames.append(QString("%1,").arg(*itC));
                vnames.append(QString("%1,").arg(*itV));
            }

            colnames.chop(1);
            vnames.chop(1);

            database->createRecord(tableName, colnames, vnames);

            return true;
        }

    }
}
