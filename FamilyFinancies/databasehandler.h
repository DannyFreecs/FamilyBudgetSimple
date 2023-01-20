#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include "databasemanager.h"
class DataBaseHandler
{
public:
    static std::unique_ptr<DataBaseManager> _dbManager;
public:
    static void initDbManager(QString &&dbPath) {
        _dbManager = std::make_unique<DataBaseManager>(std::move(dbPath));
        int z = 0;
    }
    static std::unique_ptr<DataBaseManager>& getDbManager() {
        return _dbManager;
    }
};


#endif // DATABASEHANDLER_H
