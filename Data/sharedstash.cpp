#include "sharedstash.h"
#include <exception>
#include <iostream>

namespace Data{

    void SharedStash::loadTable(const QString & tableName)
    {
        try {
            bool exists = database->tableExists(tableName);
            if(exists == false){
                database->createTable<QString, QString>(tableName, {"objectName", "objectData"});
            }
            this->tableHandler.reset(new DatabaseTableHandler(this->database.get(), tableName));
        } catch (std::ios_base::failure e) {
            handleError(tableError(), e);
        }
    }

    QString SharedStash::getObjectName(const QString &packageName, const QString &itemName)
    {
        return QString("%1_%2").arg(packageName).arg(itemName);
    }

    std::string SharedStash::setError()
    {
        return "Error while trying to set an element in the database: ";
    }

    std::string SharedStash::getError()
    {
        return "Error while trying to get an element from the database: ";
    }

    std::string SharedStash::tableError()
    {
        return "Error while loading table: ";
    }

    void SharedStash::handleError(const std::string &errorText, const std::ios_base::failure &e)
    {
        std::cerr << errorText << e.what() << std::endl;
    }

    SharedStash::SharedStash(std::shared_ptr<DatabaseConnection> databaseConnection, const QString & stashTable)
    {
        this->database = std::move(databaseConnection);
        loadTable(stashTable);
    }

    SharedStash::SharedStash(const QString & databasePath, const QString & stashTable){
        this->database.reset(new DatabaseConnection(databasePath));
        loadTable(stashTable);
    }

    QVariant SharedStash::getElement(const QString &packageName, const QString &itemName)
    {
        QVariant result{};
        try {
            QString objectName = getObjectName(packageName, itemName);

            result = tableHandler->getValueFromRow(objectName, "objectData");
        } catch (std::ios_base::failure e) {
            handleError(getError(), e);
        }

        return result;
    }

    void SharedStash::setElement(const QString &packageName, const QString & itemName, const QVariant &element)
    {
        try {
            QString objectName = getObjectName(packageName, itemName);
            if(tableHandler->keyExists(objectName)){
                tableHandler->setValueByKey(objectName, "objectData", element.toString());
            }
            else{
                tableHandler->createRecord({"objectName", "objectData"}, {objectName, element.toString()});
            }
        } catch (std::ios_base::failure e) {
            handleError(setError(), e);
        }
    }
}
