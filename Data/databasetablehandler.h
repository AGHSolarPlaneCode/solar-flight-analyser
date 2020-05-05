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
    public:
        /*!
         * \brief keyExists - check if a given primary key exists in a table
         * \param keyName - name of the key column to check in
         * \param keyValue - value of the key to look for
         * \return true if key exists, false otherwise
         */
        bool keyExists(const QString & keyName, const QString & keyValue);
        /*!
         * \brief createByKey - create an empty record holding just the record value,
         * this is mostly a helper function
         * \param keyName - name of the key column to create
         * \param keyValue - value of the key to use
         */
        void createByKey(const QString & keyName, const QString & keyValue);
        /*!
         * \brief getNameOfColumn - get name of the column at position columnID
         * \param columnId
         * \return name of the column
         */
        QString getNameOfColumn(unsigned columnId);
        /*!
         * \brief setValueByKey - sets a single field in the record (by primary key)
         * \param key - primary key value
         * \param column - column to set
         * \param value - value to set
         * \param key_idx - optional - index of primary key in the table (if there is more than one). Defaults to 0
         */
        void setValueByKey(const QString & key, const QString & column, const QString & value, int key_idx = 0);
        /*!
         * \brief setValuesByKey - sets multiple fields of a single record
         * \param key - primary key value
         * \param columns - initializer list of columns to set
         * \param values - values to be set in the respective columns
         * \param key_idx - optional - index of primary key in the table (if there is more than one). Defaults to  0
         */
        void setValuesByKey(const QString & key, const std::initializer_list<QString> & columns, const std::initializer_list<QString> & values, int key_idx = 0);
        DatabaseTableHandler(DatabaseConnection * db, const QString & tableName);
    };
}

#endif // DATABASETABLEHANDLER_H
