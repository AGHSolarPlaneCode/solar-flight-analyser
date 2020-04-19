#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <tuple>
#include <cassert>
#include <type_traits>
#include <iostream>


namespace Data {
    /*!
     * \brief The DatabaseConnection class
     * set's up the database connection and parses the database requests
     * Database should be set up after QMainApplication,
     * and deleted before the QMainApplication quits.
     *
     */
    class DatabaseConnection
    {
        bool startupFailed();
        unsigned executeCountingQuery(QString queryString);
        QString singleRecordStringReturn(QString queryString);
        void QueryCheckAndExec(QSqlQuery & query, QString queryString);
        QSqlDatabase databaseHandler;
        static QString DATABASE_CONTAINING_FOLDER;
        template<typename T>
        static QString DBTypeName()
        {
            if constexpr(std::is_same<T, int>::value){
                return "INT";
            }
            if constexpr(std::is_same<T, bool>::value){
                return "BIT";
            }
            if constexpr(std::is_convertible<T, std::string>::value){
                return "TEXT";
            }
            if constexpr(std::is_same<T, QString>::value){
                return "TEXT";
            }
            if constexpr(std::is_convertible<T, double>::value){
                return "REAL";
            }

        }
    public:
        /*!
         * \brief Check if a table with name exists in the database
         * \param tableName - name of the table to check
         * \return true if database exists, false otherwise
         * \throws std::ios_base::failure
         */
        unsigned tableExists(const QString & tableName);
        /*!
         * \brief createTable<typename ... Ts>
         * types of the columns are passed as template argument
         * i.e. createTable<int, std::string, std::string>("Tab", {"ID", "Name", "Surname"})
         * creates table "Tab" with three columns of types ID - int, Name - string, Surname - string
         * The first column is always a primary key
         * \param tableName - name of the table to create
         * \param columnNames - an initialiser list, each element containing the name of the column to create
         * \return true if table was created successfully, false otherwise
         * \throws std::ios_base::failure
         */
        template<typename ... Ts>
        bool createTable(const QString &tableName, const std::initializer_list<QString> & columnNames){
            if(!databaseHandler.isOpen())
                return false;

            constexpr size_t num_cols = sizeof...(Ts);

            assert(num_cols == columnNames.size());

            std::vector<std::tuple<QString, QString>> columnNameAndType;

            auto columnNameIterator = columnNames.begin();

            (columnNameAndType.push_back({*columnNameIterator++, DBTypeName<Ts>()}), ...);

            QString query = QString("CREATE TABLE %1(\n%2\n);").arg(tableName);
            QString insideQuery;

            unsigned ctr = 0;

            for(auto & pair : columnNameAndType){
                insideQuery += std::get<0>(pair) + " " + std::get<1>(pair);
                if(ctr == 0){
                    insideQuery += " PRIMARY KEY";
                }
                ctr++;
                if(ctr != num_cols)
                    insideQuery += ",\n";
            }

            query = query.arg(insideQuery);

            QSqlQuery executed(query);

            if(executed.isActive())
                return true;
            return false;
        }

        /*!
         * \brief Check if a record with string "ID" is used as the key,
         * if otherwise specify the key parameter
         * (if integer-string is passed as a key, it will be checking for integer values)
         * \param tableName - name of the table to check in
         * \param recordName - Identificator of the record to look for
         * \param keyCol - column in which to search for the key in
         * \return true - if the record exists, false otherwise
         * \throws std::ios_base::failure
         */
        unsigned recordExists(const QString & tableName, const QString & recordName, const QString & keyCol);
        /*!
         * \brief Returns the string representation of the requested record
         * \param tableName - name of the table to get from
         * \param recordSelector - selector of the record in SQL style - i.e. * or name='string'
         * \throws std::ios_base::failure
         * \return
         */
        QString getRecord(const QString & tableName, const QString & recordSelector);
        /*!
         * \brief Set the record to a requested value. The record will be created
         * if it doesn't exist, or it's value will be changed if it exists
         * \param tableName - name of the table to set the record in
         * \param selector of the record in SQL style - i.e. * or name='string'
         * \param recordData - data to be saved
         * \throws std::ios_base::failure
         * \return
         */
        bool setRecord(const QString & tableName, const QString & recordSelector, const QString & recordData);
        /*!
         * \brief deleteRecord - delete a record with given ID if it exists
         * \param tableName - name of the table to delete in
         * \param recordSelector - selector of the record in SQL style - i.e. * or name='string'
         * \throws std::ios_base::failure
         * \return
         */
        bool deleteRecord(const QString & tableName, const QString & recordSelector);

        /*!
         * \brief Basic constructor of the DatabaseConnection class
         * \param databasePath - path to the database file
         * \param databaseDriver - driver of the database - QSQLITE by default
         * \throws std::ios_base::failure
         */

        bool isOpen();
        DatabaseConnection(const QString & databasePath, const QString & databaseDriver = "QSQLITE");
        ~DatabaseConnection();
        DatabaseConnection(DatabaseConnection & dbCp);
        DatabaseConnection(DatabaseConnection && dbCp);
    };
}


#endif // DATABASECONNECTION_H
