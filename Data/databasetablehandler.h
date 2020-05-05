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
    public:
        QString getNameOfColumn(unsigned columnId);
        void setValueByKey(const QString & key, const QString & column, const QString & value, int key_idx = 0);
        DatabaseTableHandler(DatabaseConnection * db, const QString & tableName);
    };
}

#endif // DATABASETABLEHANDLER_H
