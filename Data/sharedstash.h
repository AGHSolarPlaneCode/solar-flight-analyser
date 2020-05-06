#ifndef SHAREDSTASH_H
#define SHAREDSTASH_H
#include <QString>
#include "databasetablehandler.h"
#include <memory>

namespace Data{
    class SharedStash
    {
        std::shared_ptr<DatabaseConnection> database;
        std::unique_ptr<DatabaseTableHandler> tableHandler;

        void loadTable(const QString & tableName);
    public:
        //use an existing database connection
        SharedStash(std::shared_ptr<DatabaseConnection> databaseConnection, const QString & stashTable = "shared_stash");
        //create a database connection
        SharedStash(const QString & databasePath, const QString & stashTable =  "shared_stash");
        auto getElement(const QString & packageName, const QString & itemName);
    };
}


#endif // SHAREDSTASH_H
