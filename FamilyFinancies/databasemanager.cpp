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

// Returns all house addresses
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

// Returns the id of the house that has the same address as the parameter
int DataBaseManager::getHouseId(const QString &address) const
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Houses WHERE Address = :address;");
    query.bindValue(":address", address);
    if (!query.exec() || !query.next()) return -1;

    return (query.exec() && query.next()) ? query.value(0).toInt() : -1;
}

// Returns the id of a house related expense category
int DataBaseManager::getHouseExpenseId(QString &&subCategory, QString &&subSubCategory) const
{
    QSqlQuery query;
    query.prepare(QString("SELECT id FROM Categories WHERE SubCategory = :sub") + QString(subSubCategory.isEmpty() ? ";" : " AND SubSubCategory = :subsub"));
    query.bindValue(":sub", subCategory);
    query.bindValue(":subsub", subSubCategory);

    return (query.exec() && query.next()) ? query.value(0).toInt() : -1;
}

// Check if a given house expense is already in the database with the correspoding date. (To see if the user wants to account again a month/year related expense)
bool DataBaseManager::checkHouseExpenseExistence(const int houseId, const QDate &when, QString &&type, QString &&subType) const
{
    int expType{getHouseExpenseId(std::move(type), std::move(subType))};
    if (expType == -1) return false;

    QSqlQuery query;
    // if insurance => use year else use year + month (bills)!
    QString dateFormat{expType == 13 ? "strftime('%Y', CreateDate)" : "strftime('%Y-%m', CreateDate)"};
    query.prepare("SELECT * FROM Expenses WHERE HouseFK = :house AND ExpenseType = :type AND " + dateFormat + " = :date;");
    query.bindValue(":house", houseId);
    query.bindValue(":type", expType);
    // if insurance => use year else use year + month (bills)!
    query.bindValue(":date", when.toString(expType == 13 ? "yyyy" : "yyyy-MM"));

    return query.exec() && query.next();
}

// Returns the cars from the database
QVector<QString> DataBaseManager::getCars() const
{
    QVector<QString> cars;
    QSqlQuery query;
    query.exec("SELECT Type FROM Cars;");

    while (query.next())
    {
        cars.append(query.value(0).toString());
    }

    return cars;
}

// Returns the children from the database
QVector<QString> DataBaseManager::getChildren() const
{
    QVector<QString> children;
    QSqlQuery query;
    query.exec("SELECT Name FROM Children;");

    while (query.next())
    {
        children.append(query.value(0).toString());
    }

    return children;
}

// Returns the shopping related categories ids and names
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

// Returns the fix house expenses (every year/month same cost as before)
QMap<QString, int> DataBaseManager::getHouseFixCosts() const
{
    QMap<QString, int> fixCosts;;

    QSqlQuery query;
    query.exec("Select SubCategory, SubSubCategory, FixAmount FROM Categories WHERE Category = 'Ház' AND Fix = 1;");

    while (query.next())
    {
        // if the SubSubCategory is NULL => This is the 'Insurance', else it is bill (water, gas, etc.)
        fixCosts.insert(query.isNull(1) ? query.value(0).toString() : query.value(1).toString(), query.value(2).toInt());
    }

    return fixCosts;
}

// Inserts records of a receipt into the database
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

// Inserts 1 shopping relatzed expense into the database
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

// Inserts the bills of a house (water, net, electricity, etc.)
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

// Modifies a bill that is already in the database
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
