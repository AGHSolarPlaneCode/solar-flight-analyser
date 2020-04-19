#include "databaseconnection.h"
#include <QFileInfo>
#include <QDir>
#include <QVariant>

namespace Data{

    QString Data::DatabaseConnection::DATABASE_CONTAINING_FOLDER = "Database";

    DatabaseConnection::DatabaseConnection(const QString &databasePath, const QString &databaseDriver)
    {
        if(!QSqlDatabase::isDriverAvailable(databaseDriver))
            throw std::ios_base::failure("Driver of name " + databaseDriver.toStdString() + " isn't available.");

        bool folderExists = QFileInfo::exists(DATABASE_CONTAINING_FOLDER) && QFileInfo(DATABASE_CONTAINING_FOLDER).isDir();
        if(!folderExists){
            QDir().mkpath(DATABASE_CONTAINING_FOLDER);
        }

        databaseHandler = QSqlDatabase::addDatabase(databaseDriver);
        databaseHandler.setDatabaseName(databasePath);
        databaseHandler.open();
    }

    DatabaseConnection::~DatabaseConnection()
    {
        if(databaseHandler.isOpen())
            databaseHandler.close();
    }

    DatabaseConnection::DatabaseConnection(DatabaseConnection &&dbCp)
    {
        this->databaseHandler = std::move(dbCp.databaseHandler);
    }

    DatabaseConnection::DatabaseConnection(DatabaseConnection &dbCp)
    {
        if(dbCp.databaseHandler.isOpen()){
            this->databaseHandler = QSqlDatabase::cloneDatabase(dbCp.databaseHandler, dbCp.databaseHandler.databaseName());
            this->databaseHandler.open();
        }
    }

    void DatabaseConnection::QueryCheckAndExec(QSqlQuery &query, QString queryString)
    {
        if(!databaseHandler.isOpen())
            throw std::ios_base::failure("Database was not open when query was requested: " + queryString.toStdString());

        query.exec(queryString);

        if(!query.isActive())
            throw std::ios_base::failure("Could not execute a query: " + queryString.toStdString());

    }

    unsigned DatabaseConnection::executeCountingQuery(QString queryString)
    {

        QSqlQuery query(databaseHandler);

        QueryCheckAndExec(query, queryString);

        query.last();
        return query.value(0).toUInt();
    }

    QString DatabaseConnection::singleRecordStringReturn(QString queryString)
    {
        QSqlQuery query(databaseHandler);

        QueryCheckAndExec(query, queryString);

        query.last();
        return query.value(0).toString();
    }

    unsigned DatabaseConnection::recordExists(const QString &tableName, const QString &recordName, const QString & keyCol)
    {
        return executeCountingQuery(
                    QString("SELECT count(%1) FROM %2 WHERE %3='%4'").arg(keyCol).arg(tableName).arg(keyCol).arg(recordName)
                    );
    }

    unsigned DatabaseConnection::tableExists(const QString &tableName)
    {
        return executeCountingQuery(
                    QString("SELECT count(name) FROM sqlite_master WHERE type='table' AND name='%1';").arg(tableName)
                    );
    }

    QString getRecord(const QString &tableName, const QString &recordSelector)
    {

    }

    bool DatabaseConnection::isOpen()
    {
        return databaseHandler.isOpen();
    }

}

