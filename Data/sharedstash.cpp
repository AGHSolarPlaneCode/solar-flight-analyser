#include "sharedstash.h"

namespace Data{

    void SharedStash::loadTable(const QString & tableName)
    {
        bool exists = database->tableExists(tableName);
        if(exists == false){
            database->createTable<QString, QString>(tableName, {"objectName", "objectData"});
        }
        this->tableHandler.reset(new DatabaseTableHandler(this->database.get(), tableName));
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

    auto SharedStash::getElement(const QString &packageName, const QString &itemName)
    {
        QString objectName = QString("%1_%2").arg(packageName).arg(itemName);
        //TODO
        //this->tableHandler->
    }
}
