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

    QSqlQuery DatabaseConnection::executeQuery(const QString & query){
        if(!databaseHandler.isOpen())
            throw databaseClosedErrorMessage(query);

        QSqlQuery ret;
        ret.exec(query);

        if(!ret.isActive())
            throw queryFailedErrorMessage(query);
        return ret;
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

    QVector<QPair<QString, bool>> DatabaseConnection::getTableColumns(const QString & tableName){
        QSqlQuery q = executeQuery(QString("PRAGMA table_info(%1)").arg(tableName));

        QVector<QPair<QString, bool>> tableInfo;

        while(q.next()){
            tableInfo.push_back(
                        qMakePair<QString, bool>(
                            q.value(1).toString(),
                            q.value(5).toBool()
                            )
                        );
        }

        return tableInfo;
    }

    bool DatabaseConnection::recordExists(const QString &tableName, const QString &selector)
    {
        return executeCountingQuery(
                    QString(
                        "SELECT COUNT(*) FROM %1 WHERE %2")
                        .arg(tableName).arg(selector)
                        );
    }

    QVector<QPair<QString, QString>> selectorSeparator(const QString & selector){
        QStringList list = selector.split(QRegExp("[\\s|,]+"), QString::SkipEmptyParts);
        QVector<QPair<QString, QString>> r;
        for(int i = 0; i < list.size(); i+=2){
            r.push_back(qMakePair(list.at(i), list.at(i+1)));
        }
        return r;
    }

    void DatabaseConnection::createRecord(const QString &tableName, const QString &columns, const QString &values){
        QString query = "INSERT INTO %1 (%2) VALUES (%3)";
        query = query.arg(tableName).arg(columns).arg(values);
        executeQuery(query);
    }

    bool DatabaseConnection::updateRecord(const QString &tableName, const QString &selector, const QString &values){

        bool ex = recordExists(tableName, selector);

        if(ex == true){
            QString query = QString(
                        "UPDATE %1 SET %2 WHERE %3"
                        ).arg(tableName).arg(values).arg(selector);
            executeQuery(query);
        }


        return ex;
    }


    bool DatabaseConnection::isOpen()
    {
        return databaseHandler.isOpen();
    }

}
