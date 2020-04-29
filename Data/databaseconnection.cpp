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
            throw databaseClosedErrorMessage(queryString);


        query.exec(queryString);

        if(!query.isActive())
            throw queryFailedErrorMessage(queryString);
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


    unsigned DatabaseConnection::tableExists(const QString &tableName)
    {
        return executeCountingQuery(
                    QString("SELECT count(name) FROM sqlite_master WHERE type='table' AND name='%1';").arg(tableName)
                    );
    }

    std::ios_base::failure DatabaseConnection::databaseClosedErrorMessage(const QString &query){
        if(query != ""){
            return std::ios_base::failure("Database was not open when query was requested: " + query.toStdString());
        }
        else{
            return std::ios_base::failure("Database isn't open.");
        }
    }

    std::ios_base::failure DatabaseConnection::queryFailedErrorMessage(const QString &query){
        if(query != ""){
            return std::ios_base::failure("Could not execute a query: " + query.toStdString());
        }
        else{
            return  std::ios_base::failure("A query has failed");
        }
    }

    std::vector<std::tuple<QString, bool>> DatabaseConnection::getTableColumns(const QString & tableName){
        QSqlQuery q = executeQuery(QString("PRAGMA table_info(%1)").arg(tableName));

        std::vector<std::tuple<QString, bool>> tableInfo;

        while(q.next()){
            tableInfo.emplace_back(
                        std::make_tuple<QString, bool>(
                            q.value(1).toString(),
                            q.value(5).toBool()
                            )
                        );
        }

        return tableInfo;

    unsigned DatabaseConnection::tableExists(const QString &tableName)
    {
        return executeCountingQuery(
                    QString("SELECT count(name) FROM sqlite_master WHERE type='table' AND name='%1';").arg(tableName)
                    );
    }

    bool DatabaseConnection::isOpen()
    {
        return databaseHandler.isOpen();
    }

}

