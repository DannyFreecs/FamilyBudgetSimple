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
int DataBaseManager::getHouseId(QString &&address) const
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Houses WHERE Address = :address;");
    query.bindValue(":address", address);
    if (!query.exec() || !query.next()) return -1;

    return (query.exec() && query.next()) ? query.value(0).toInt() : -1;
}

// Returns the id of a house related expense category
int DataBaseManager::getCategoryId(QString &&category, QString &&subCategory, QString &&subSubCategory) const
{
    QSqlQuery categoryQuery;
    QString query("SELECT id FROM Categories WHERE Category = '" + category + "'");
    if (!subCategory.isEmpty()) query.append("AND SubCategory = '" + subCategory + "'");
    if (!subSubCategory.isEmpty()) query.append("AND SubSubCategory = '" + subSubCategory + "'");
    query.append(';');

    categoryQuery.prepare(query);
    categoryQuery.bindValue(":sub", subCategory);
    categoryQuery.bindValue(":subsub", subSubCategory);

    return (categoryQuery.exec() && categoryQuery.next()) ? categoryQuery.value(0).toInt() : -1;
}

// Check if a given house expense is already in the database with the correspoding date. (To see if the user wants to account again a month/year related expense)
bool DataBaseManager::checkHouseExpenseExistence(QString&& house, const QDate &when, QString &&type, QString &&subType) const
{
    int houseID = getHouseId(std::move(house));
    if (houseID == -1) return false;
    int expType{getCategoryId("Ház", std::move(type), std::move(subType))};
    if (expType == -1) return false;

    QSqlQuery query;
    // if insurance => use year else use year + month (bills)!
    QString dateFormat{expType == 13 ? "strftime('%Y', CreateDate)" : "strftime('%Y-%m', CreateDate)"};
    query.prepare("SELECT * FROM Expenses WHERE HouseFK = :house AND ExpenseType = :type AND " + dateFormat + " = :date;");
    query.bindValue(":house", houseID);
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
QMap<QString, int> DataBaseManager::getHouseLastFixCosts(QString &&address) const
{
    int houseID = getHouseId(std::move(address));
    QMap<QString, int> fixCosts;

    QSqlQuery catQuery;
    catQuery.exec("Select SubCategory, SubSubCategory FROM Categories WHERE Category = 'Ház' AND Fix = 1;");

    QSqlQuery lastCost;
    lastCost.prepare("SELECT Cost FROM Expenses WHERE ExpenseType = :type AND HouseFK = :house ORDER BY CreateDate DESC LIMIT 1;");
    while (catQuery.next())
    {
        lastCost.bindValue(":type", getCategoryId("Ház", catQuery.value(0).toString(), catQuery.isNull(1) ? "" : catQuery.value(1).toString()));
        lastCost.bindValue(":house", houseID);

        lastCost.exec();
        lastCost.next();

        // if the SubSubCategory is NULL => This is the 'Insurance', else it is a type of 'Bill' (water, gas, etc.)
        fixCosts.insert(catQuery.isNull(1) ? catQuery.value(0).toString() : catQuery.value(1).toString(), lastCost.value(0).toInt());

        lastCost.finish();
    }

    return fixCosts;
}

int DataBaseManager::getChildId(const QString &child) const
{
    QSqlQuery query;
    query.prepare("Select id FROM Children WHERE Name = :name;");
    query.bindValue(":name", child);

    if (!query.exec() || !query.next()) return -1;

    return query.value(0).toInt();
}

int DataBaseManager::getChildStudyLastCost(const QString &child) const
{
    int childID = getChildId(child);
    int expType = getCategoryId("Gyerek", "Tanulmány");
    QSqlQuery query;
    query.prepare("Select Cost FROM Expenses WHERE ExpenseType = :type AND ChildFK = :child ORDER BY CreateDate DESC LIMIT 1;");
    query.bindValue(":type", expType);
    query.bindValue(":child", childID);

    if (!query.exec() || !query.next()) return -1;

    return query.value(0).toInt();
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
bool DataBaseManager::insertHouseBills(QString &&house, const QDate &date, QVector<std::pair<QString, int>> &&bills) const
{
    int houseID = getHouseId(std::move(house));
    if (houseID == -1)
    {
        QMessageBox::critical(nullptr, "Hiba", "Nem sikerült a házat elérni az adatbázisban!");
        return false;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Expenses(Cost, CreateDate, ExpenseType, HouseFK) VALUES(?, ?, ?, ?);");
    QVariantList costs;
    QVariantList dates;
    QVariantList types;
    QVariantList houseFK;

    for(auto& bill : bills)
    {
        costs   << bill.second;
        dates   << date.toString("yyyy-MM-dd");
        types   << getCategoryId("Ház", "Rezsi", std::move(bill.first));
        houseFK << houseID;
    }

    insertQuery.addBindValue(costs);
    insertQuery.addBindValue(dates);
    insertQuery.addBindValue(types);
    insertQuery.addBindValue(houseFK);

    return insertQuery.execBatch();
}

// Modifies a bill that is already in the database
bool DataBaseManager::updateHouseBills(QString &&house, const QDate &date, QVector<std::pair<QString, int> > &&bills) const
{
    int houseID = getHouseId(std::move(house));
    if (houseID == -1)
    {
        QMessageBox::critical(nullptr, "Hiba", "Nem sikerült a házat elérni az adatbázisban!");
        return false;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Expenses SET Cost = ? WHERE id = ?;");

    QVariantList costs;
    QVariantList ids;

    QSqlQuery idQuery;
    idQuery.prepare("SELECT id FROM Expenses WHERE HouseFK = :house AND ExpenseType = :type AND strftime('%Y-%m', CreateDate) = :date;");
    idQuery.bindValue(":house", houseID);
    idQuery.bindValue(":date", date.toString("yyyy-MM"));

    for(auto& bill : bills)
    {
        idQuery.bindValue(":type", getCategoryId("Ház", "Rezsi", std::move(bill.first)));
        if (!idQuery.exec() || !idQuery.next()) return false;

        costs << bill.second;
        ids   << idQuery.value(0).toInt();
    }

    updateQuery.addBindValue(costs);
    updateQuery.addBindValue(ids);

    return updateQuery.execBatch();
}

bool DataBaseManager::insertHouseInsurance(QString &&house, const QDate &date, const int cost) const
{
    int houseID = getHouseId(std::move(house));
    if (houseID == -1)
    {
        QMessageBox::critical(nullptr, "Hiba", "Nem sikerült a házat elérni az adatbázisban!");
        return false;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Expenses(Cost, CreateDate, ExpenseType, HouseFK) VALUES(:cost, :date, :type, :house);");
    insertQuery.bindValue(":cost", cost);
    insertQuery.bindValue(":date", QDate(date.year(), 1, 1).toString("yyyy-MM-dd"));
    insertQuery.bindValue(":type", getCategoryId("Ház", "Biztosítás"));
    insertQuery.bindValue(":house", houseID);

    return insertQuery.exec();
}

bool DataBaseManager::updateHouseInsurance(QString &&house, const QDate &date, const int cost) const
{
    int houseID = getHouseId(std::move(house));
    if (houseID == -1)
    {
        QMessageBox::critical(nullptr, "Hiba", "Nem sikerült a házat elérni az adatbázisban!");
        return false;
    }

    QSqlQuery idQuery;
    idQuery.prepare("SELECT id FROM Expenses WHERE HouseFK = :house AND ExpenseType = :type AND strftime('%Y', CreateDate) = :date;");
    idQuery.bindValue(":house", houseID);
    idQuery.bindValue(":type", getCategoryId("Ház", "Biztosítás"));
    idQuery.bindValue(":date", date.toString("yyyy"));
    if (!idQuery.exec() || !idQuery.next()) return false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Expenses SET Cost = :cost WHERE id = :id;");
    updateQuery.bindValue(":cost", cost);
    updateQuery.bindValue(":id", idQuery.value(0).toInt());

    return updateQuery.exec();
}

bool DataBaseManager::insertHouseOtherExpense(QString &&house, QMap<QString, QString> &&item) const
{
    int houseID = getHouseId(std::move(house));
    if (houseID == -1)
    {
        QMessageBox::critical(nullptr, "Hiba", "Nem sikerült a házat elérni az adatbázisban!");
        return false;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Expenses(Cost, Comment, CreateDate, ExpenseType, HouseFK) VALUES(:cost, :comment, :date, :type, :house)");
    insertQuery.bindValue(":cost", item["cost"].toInt());
    insertQuery.bindValue(":comment", item["comment"]);
    insertQuery.bindValue(":date", item["date"]);
    insertQuery.bindValue(":type", getCategoryId("Ház", "Egyéb"));
    insertQuery.bindValue(":house", houseID);

    return insertQuery.exec();
}
