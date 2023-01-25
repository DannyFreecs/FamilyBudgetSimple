#include "databasemanager.h"
#include <QMessageBox>
#include <QSqlError>

DataBaseManager::DataBaseManager(QString&& dbpath) : _dbPath(dbpath)
{
    connect();
}

void DataBaseManager::connect()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(_dbPath);

    if(!_db.open())
    {
        QMessageBox::critical(0, "Error", "Failed to connect to the database.\nError: " + _db.lastError().text() + "\nPlease contact the operator!");
        return;
    }
}

QVector<QString> DataBaseManager::getHouses()
{
    QVector<QString> houses;
    QSqlQuery query;
    query.exec("SELECT Address FROM Houses");

    while (query.next())
    {
        houses.append(query.value(0).toString());
    }

    return houses;
}

QVector<QString> DataBaseManager::getCars()
{
    QVector<QString> houses;
    QSqlQuery query;
    query.exec("SELECT Type FROM Cars");

    while (query.next())
    {
        houses.append(query.value(0).toString());
    }

    return houses;
}

QVector<QString> DataBaseManager::getChildren()
{
    QVector<QString> houses;
    QSqlQuery query;
    query.exec("SELECT Name FROM Children");

    while (query.next())
    {
        houses.append(query.value(0).toString());
    }

    return houses;
}

QStringList DataBaseManager::getShoppingCategories()
{
    QStringList categories;

    QSqlQuery query;
    query.exec("SELECT SubCategory FROM Categories WHERE Category = 'Vásárlás'");

    while (query.next())
    {
        categories.append(query.value(0).toString());
    }

    return categories;
}

void DataBaseManager::insertShoppingExpanse(QVector<QVector<QString> > &&shoppingData)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Expanses(...) VALUES(?, ?, ?, ?)");
    QVariantList amounts;
    QVariantList categories;
    QVariantList dates;
    QVariantList comments;

    for(const auto& row : shoppingData)
    {
        amounts    << row[0];
        categories << row[1];
        dates      << row[2];
        comments   << row[3];
    }

    query.addBindValue(amounts);
    query.addBindValue(categories);
    query.addBindValue(dates);
    query.addBindValue(comments);

    query.execBatch();
}
