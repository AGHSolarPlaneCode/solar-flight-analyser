#ifndef SHAREDSTASH_H
#define SHAREDSTASH_H
#include <QString>
#include "databasetablehandler.h"
#include <memory>
#include <QVariant>
#include <exception>

namespace Data{
    class SharedStash
    {
        std::shared_ptr<DatabaseConnection> database;
        std::unique_ptr<DatabaseTableHandler> tableHandler;

        void loadTable(const QString & tableName);
        QString getObjectName(const QString & packageName, const QString & itemName);

        std::string setError();
        std::string getError();
        std::string tableError();

        void handleError(const std::string & errorText, const std::ios_base::failure & e);

    public:
        //use an existing database connection
        SharedStash(std::shared_ptr<DatabaseConnection> databaseConnection, const QString & stashTable = "shared_stash");
        //create a database connection
        SharedStash(const QString & databasePath, const QString & stashTable =  "shared_stash");
        /*!
         * \brief getElement - get an element from the stash
         * \param packageName - name of the package
         * \param itemName - name of the element
         * \return QVariant containing the element
         */
        QVariant getElement(const QString & packageName, const QString & itemName);
        /*!
         * \brief setElement - set an element in the stash (or create one if it doesn't exist)
         * \param packageName - name of the package
         * \param itemName - name of the element
         * \param element - value of the element
         *
         */
        void setElement(const QString & packageName, const QString & itemName, const QVariant & element);
    };
}


#endif // SHAREDSTASH_H
