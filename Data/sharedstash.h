#ifndef SHAREDSTASH_H
#define SHAREDSTASH_H
#include <QString>
#include "databaseconnection.h"

namespace Data{
    class SharedStash
    {
    public:
        //use an existing database connection
        SharedStash(const DatabaseConnection * databaseConnection);
        //create a database connection
        SharedStash(const QString & databasePath);
        auto getElement(const QString & packageName, const QString & itemName);
    };
}


#endif // SHAREDSTASH_H
