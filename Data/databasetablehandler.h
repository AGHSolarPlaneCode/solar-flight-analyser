#ifndef DATABASETABLEHANDLER_H
#define DATABASETABLEHANDLER_H

#include "databaseconnection.h"
#include <vector>
#include <stdexcept>
#include <tuple>

namespace Data {
    class DatabaseTableHandler
    {
        DatabaseConnection * database;
        QString tableName;
        QVector<QPair<QString, bool>> columnNames;
        void fetchColumns();
        QString getFirstKeyName(int key_idx);
        QString getKeySelector(const QString & keyValue, int key_idx = 0);
    public:
        /*!
         * \brief keyExists - check if a given primary key exists in a table
         * \param keyName - name of the key column to check in
         * \param keyValue - value of the key to look for
         * \return true if key exists, false otherwise
         * \throws std::ios_base::error
         */
        bool keyExists(const QString & keyName, const QString & keyValue);
        /*!
         * \brief check if a given primary key exists in a table
         * \param keyValue - value of the key to look for
         * \param key_idx - index of the key if more than one primary keys exist in the table
         * \return true if key exists, false otherwise
         * \throws std::ios_base::error
         */
        bool keyExists(const QString & keyValue, int key_idx = 0);
        /*!
         * \brief createByKey - create an empty record holding just the record value,
         * this is mostly a helper function
         * \param keyName - name of the key column to create
         * \param keyValue - value of the key to use
         * \throws std::ios_base::error
         */
        void createByKey(const QString & keyName, const QString & keyValue);
        /*!
         * \brief getNameOfColumn - get name of the column at position columnID
         * \param columnId
         * \return name of the column
         * \throws std::ios_base::error
         */
        QString getNameOfColumn(unsigned columnId);
        /*!
         * \brief setValueByKey - sets a single field in the record (by primary key)
         * \param key - primary key value
         * \param column - column to set
         * \param value - value to set
         * \param key_idx - optional - index of primary key in the table (if there is more than one). Defaults to 0
         * \throws std::ios_base::error
         */
        void setValueByKey(const QString & key, const QString & column, const QString & value, int key_idx = 0);
        /*!
         * \brief setValuesByKey - sets multiple fields of a single record
         * \param key - primary key value
         * \param columns - initializer list of columns to set
         * \param values - values to be set in the respective columns
         * \param key_idx - optional - index of primary key in the table (if there is more than one). Defaults to  0
         * \throws std::ios_base::error
         */
        void setValuesByKey(const QString & key, const std::initializer_list<QString> & columns, const std::initializer_list<QString> & values, int key_idx = 0);
        /*!
         * \brief getValueFromRow - get requested value (column) from a row where primary key is equal to key
         * \param key - value of the primary key
         * \param columnName - name of the column to return
         * \param key_idx - index of the primary key in the table, defaults to 0 (the first primary key)
         * \return QVariant of the requested value
         * \throws std::ios_base::error
         */
        QVariant getValueFromRow(const QString & key, const QString & columnName, int key_idx = 0);

        /*!
         * \brief createRecord - create a new record in the database. The first column on the list MUST be a primary key
         * \param columns - list of columns to be set
         * \param values - list of values to be set in their respective columns
         * \return true if the record was created,  false if a record with such a key already exists in the database.
         * \throws std::ios_base::error
         */
        bool createRecord(const std::initializer_list<QString> & columns, const std::initializer_list<QString> & values);
        /*!
         * \brief createRecord - in this version of createRecord only values are specified, and default column
         * names are used in their respective order
         * \param values - values of the columns to be set
         * \return  true if the record was created, false otherwise
         */
        bool createRecord(const std::initializer_list<QString> & values);

        DatabaseTableHandler(DatabaseConnection * db, const QString & tableName);
    };
}

#endif // DATABASETABLEHANDLER_H
