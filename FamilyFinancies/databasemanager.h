#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include <QSqlDatabase>
#include <QSqlQuery>

class DataBaseManager
{
public:
    DataBaseManager(QString&& dbpath);

    void connect();
    QVector<QString> getHouses();
    QVector<QString> getCars();
    QVector<QString> getChildren();

private:
    QSqlDatabase _db;
    QString _dbPath;
};

#endif // DATABASEMANAGER_H
