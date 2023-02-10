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

QVector<QString> DataBaseManager::getHouses() const
{
    QVector<QString> houses;
    QSqlQuery query;
    query.exec("SELECT Address FROM Houses;");

    while (query.next())
    {
        houses.append(query.value(0).toString());
    }

    return houses;
}

int DataBaseManager::getHouseId(const QString &address) const
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Houses WHERE Address = :address;");
    query.bindValue(":address", address);
    if (!query.exec() || !query.next()) return -1;

    return (query.exec() && query.next()) ? query.value(0).toInt() : -1;
}

int DataBaseManager::getHouseExpenseId(QString &&subCategory, QString &&subSubCategory) const
{
    QSqlQuery query;
    query.prepare(QString("SELECT id FROM Categories WHERE SubCategory = :sub") + QString(subSubCategory.isEmpty() ? ";" : " AND SubSubCategory = :subsub"));
    query.bindValue(":sub", subCategory);
    query.bindValue(":subsub", subSubCategory);

    return (query.exec() && query.next()) ? query.value(0).toInt() : -1;
}

bool DataBaseManager::checkHouseExpenseExistence(const int houseId, const QDate &when, QString &&type, QString &&subType) const
{
    int expType{getHouseExpenseId(std::move(type), std::move(subType))};
    if (expType == -1) return false;

    QSqlQuery query;
    // ha biztositas => evet kell nezni nem ev + honapot!
    QString dateFormat{expType == 13 ? "strftime('%Y', CreateDate)" : "strftime('%Y-%m', CreateDate)"};
    query.prepare("SELECT * FROM Expenses WHERE HouseFK = :house AND ExpenseType = :type AND " + dateFormat + " = :date;");
    query.bindValue(":house", houseId);
    query.bindValue(":type", expType);
    // ha biztositas => evet kell nezni nem ev + honapot!
    query.bindValue(":date", when.toString(expType == 13 ? "yyyy" : "yyyy-MM"));

    return query.exec() && query.next();
}

QVector<QString> DataBaseManager::getCars() const
{
    QVector<QString> houses;
    QSqlQuery query;
    query.exec("SELECT Type FROM Cars;");

    while (query.next())
    {
        houses.append(query.value(0).toString());
    }

    return houses;
}

QVector<QString> DataBaseManager::getChildren() const
{
    QVector<QString> houses;
    QSqlQuery query;
    query.exec("SELECT Name FROM Children;");

    while (query.next())
    {
        houses.append(query.value(0).toString());
    }

    return houses;
}

QMap<QString, QString> DataBaseManager::getShoppingCategories() const
{
    QMap<QString, QString> categories;

    QSqlQuery query;
    query.exec("SELECT id, SubCategory FROM Categories WHERE Category = 'Vásárlás';");

    while (query.next())
    {
        categories.insert(query.value(0).toString(), query.value(1).toString());
    }

    return categories;
}

QMap<QString, int> DataBaseManager::getHouseFixCosts() const
{
    QMap<QString, int> fixCosts;;

    QSqlQuery query;
    query.exec("Select SubCategory, SubSubCategory, FixAmount FROM Categories WHERE Category = 'Ház' AND Fix = 1;");

    while (query.next())
    {
        fixCosts.insert(query.isNull(1) ? query.value(0).toString() : query.value(1).toString(), query.value(2).toInt());
    }

    return fixCosts;
}

bool DataBaseManager::insertShoppingReceipt(QVector<QVector<QString>> &&shoppingData) const
{
    QSqlQuery query;

    query.prepare("INSERT INTO Expenses(Cost, Comment, CreateDate, ExpenseType) VALUES(?, ?, ?, ?);");
    QVariantList costs;
    QVariantList types;
    QVariantList dates;
    QVariantList comments;

    for(const auto& row : shoppingData)
    {
        costs    << row[0].toInt();
        types    << row[1].toInt();
        dates    << row[2];
        comments << row[3];
    }

    query.addBindValue(costs);
    query.addBindValue(comments);
    query.addBindValue(dates);
    query.addBindValue(types);

    return query.execBatch();
}

bool DataBaseManager::insertShoppingItem(QVector<QString> &&itemData) const
{
    QSqlQuery query;

    query.prepare("INSERT INTO Expenses(Cost, Comment, CreateDate, ExpenseType) VALUES(:cost, :comment, :created, :type);");
    query.bindValue(":cost", itemData[0].toInt());
    query.bindValue(":comment", itemData[1]);
    query.bindValue(":created", itemData[2]);
    query.bindValue(":type", itemData[3].toInt());

    return query.exec();
}

bool DataBaseManager::insertHouseBills(const QString &house, const QDate &date, QVector<std::pair<QString, int>> &&bills) const
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Houses WHERE Address = :address;");
    query.bindValue(":address", house);
    if (!query.exec() || !query.next())
    {
        QMessageBox::critical(nullptr, "Hiba", "Nem sikerült a házat elérni az adatbázisban!");
        return false;
    }

    int houseID = query.value(0).toInt();
    query.clear();
    query.prepare("INSERT INTO Expenses(Cost, CreateDate, ExpenseType, HouseFK) VALUES(?, ?, ?, ?);");
    QVariantList costs;
    QVariantList dates;
    QVariantList types;
    QVariantList houseFK;

    for(auto& bill : bills)
    {
        costs   << bill.second;
        dates   << date.toString("yyyy-MM-dd");
        types   << getHouseExpenseId("Rezsi", std::move(bill.first));
        houseFK << houseID;
    }

    query.addBindValue(costs);
    query.addBindValue(dates);
    query.addBindValue(types);
    query.addBindValue(houseFK);

    return query.execBatch();
}

bool DataBaseManager::updateHouseBills(const QString &house, const QDate &date, QVector<std::pair<QString, int> > &&bills) const
{
    QSqlQuery houseQuery;
    houseQuery.prepare("SELECT id FROM Houses WHERE Address = :address;");
    houseQuery.bindValue(":address", house);
    if (!houseQuery.exec() || !houseQuery.next())
    {
        QMessageBox::critical(nullptr, "Hiba", "Nem sikerült a házat elérni az adatbázisban!");
        return false;
    }

    int houseID = houseQuery.value(0).toInt();

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Expenses SET Cost = ? WHERE id = ?;");

    QVariantList costs;
    QVariantList ids;

    QSqlQuery typeQuery;
    typeQuery.prepare("SELECT id FROM Expenses WHERE HouseFK = :house AND ExpenseType = :type AND strftime('%Y-%m', CreateDate) = :date;");
    typeQuery.bindValue(":house", houseID);
    typeQuery.bindValue(":date", date.toString("yyyy-MM"));

    for(auto& bill : bills)
    {
        typeQuery.bindValue(":type", getHouseExpenseId("Rezsi", std::move(bill.first)));
        if (!typeQuery.exec() || !typeQuery.next()) return false;

        costs << bill.second;
        ids   << typeQuery.value(0).toInt();
    }

    updateQuery.addBindValue(costs);
    updateQuery.addBindValue(ids);

    return updateQuery.execBatch();
}
