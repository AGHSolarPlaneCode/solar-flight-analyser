#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <stdexcept>
#include <initializer_list>
#include <QVector>
#include <QPair>
#include <cassert>
#include <type_traits>


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
        unsigned executeCountingQuery(QString queryString);
        QString singleRecordStringReturn(QString queryString);
        void QueryCheckAndExec(QSqlQuery & query, QString queryString);

        QSqlDatabase databaseHandler;

        std::ios_base::failure databaseClosedErrorMessage(const QString & query = "");
        std::ios_base::failure queryFailedErrorMessage(const QString & query = "");

        QVector<QPair<QString, QString>> selectorSeparator(const QString & selector);

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

            QVector<QPair<QString, QString>> columnNameAndType;

            auto columnNameIterator = columnNames.begin();

            (columnNameAndType.push_back({*columnNameIterator++, DBTypeName<Ts>()}), ...);

            QString query = QString("CREATE TABLE %1(\n%2\n);").arg(tableName);
            QString insideQuery;

            unsigned ctr = 0;

            for(auto & pair : columnNameAndType){
                insideQuery += pair.first + " " + pair.second;
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
         * \brief executeQuery - execute any SQL query
         * \param query - QString containing the query
         * \return returns the QSqlQuery object
         * \throws std::ios_base::failure
         */
        QSqlQuery executeQuery(const QString & query);

        /*!
         * \brief recordExists - check if a record exists in database
         * \param tableName - name of the table to check
         * \param selector - SQL selector of the record, i.e. age='40',sex='M'
         * \return true if the record exists, false otherwise
         */
        bool recordExists(const QString & tableName, const QString & selector);

        /*!
         * \brief updateRecord - updates the requested record in the table
         * accordingly to 'selector', and sets the columns specified in 'values'.
         * for example:
         *  updateRecord("users", "age=40", "payout='5000',bonus='1000'");
         * will set payout to 5000 and bonus to 1000 for all users with age 40.
         *
         * \param tableName - name of the table to use
         * \param value is an SQL type selector i. e. name='Ann', surname='Smith'
         * \param selector is an SQL type selector
         * \return returns true if an object was updated, and false if it doesn't exist.
         * \throws std::ios_base::failure
         */
        bool updateRecord(const QString & tableName, const QString & selector, const QString & values);

        /*!
         * \brief createRecord - create a record with requested columns set to values
         * \param tableName - name of the table
         * \param columns - comma separated names of columns
         * \param values - comma separated values to set in the columns
         */
        void createRecord(const QString & tableName, const QString & columns, const QString & values);

        /*!
         * \brief getTableColumns - returns the columns of a table as a Pair
         * where first is the column name, and second is a boolean value
         * indicating that this column is a primary key
         * \param tableName - name of table to check
         * \return Vector of pairs <QString, bool>
         * \throws std::ios_base::failure
         */
        QVector<QPair<QString, bool>> getTableColumns(const QString & tableName);

        bool isOpen();
        /*!
         * \brief Basic constructor of the DatabaseConnection class
         * \param databasePath - path to the database file
         * \param databaseDriver - driver of the database - QSQLITE by default
         * \throws std::ios_base::failure
         */
        DatabaseConnection(const QString & databasePath, const QString & databaseDriver = "QSQLITE");
        ~DatabaseConnection();
        DatabaseConnection(DatabaseConnection & dbCp);
        DatabaseConnection(DatabaseConnection && dbCp);
    };
}


#endif // DATABASECONNECTION_H
