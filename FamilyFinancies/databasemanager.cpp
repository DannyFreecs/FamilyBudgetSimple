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
        QMessageBox::critical(nullptr, "Error", "Failed to connect to the database.\nError: " + _db.lastError().text() + "\nPlease contact the operator!");
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

QMap<QString, QString> DataBaseManager::getShoppingCategories()
{
    QMap<QString, QString> categories;

    QSqlQuery query;
    query.exec("SELECT id, SubCategory FROM Categories WHERE Category = 'Vásárlás'");

    while (query.next())
    {
        categories.insert(query.value(0).toString(), query.value(1).toString());
    }

    return categories;
}

bool DataBaseManager::insertShoppingExpanse(QVector<QVector<QString> > &&shoppingData)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Expenses(Cost, Comment, CreateDate, ExpenseType) VALUES(?, ?, ?, ?)");
    QVariantList costs;
    QVariantList types;
    QVariantList dates;
    QVariantList comments;

    for(const auto& row : shoppingData)
    {
        costs      << row[0].toInt();
        types      << row[1].toInt();
        dates      << row[2];
        comments   << row[3];
    }

    query.addBindValue(costs);
    query.addBindValue(comments);
    query.addBindValue(dates);
    query.addBindValue(types);

    if (!query.execBatch())
    {
        return false;
    }
    return true;
}
