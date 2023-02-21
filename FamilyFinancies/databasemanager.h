#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>

class DataBaseManager
{
public:
    DataBaseManager(QString&& dbpath);

    void connect();
    int getCategoryId(QString &&category, QString &&subCategory = "", QString &&subSubCategory = "") const;
    QVector<QString> getHouses() const;
    int getHouseId(const QString &address) const;
    bool checkHouseExpenseExistence(const int houseId, const QDate &when, QString &&type, QString &&subType = "") const;
    QVector<QString> getCars() const;
    QVector<QString> getChildren() const;
    QMap<QString, QString> getShoppingCategories() const;
    QMap<QString, int> getHouseFixCosts() const;
    int getChildId(const QString &child) const;
    int getChildStudyLastCost(const QString &child) const;


    bool insertShoppingReceipt(QVector<QVector<QString>> &&shoppingData) const;
    bool insertShoppingItem(QVector<QString> &&itemData) const;
    bool insertHouseBills(const QString &house, const QDate &date, QVector<std::pair<QString, int>> &&bills) const;
    bool updateHouseBills(const QString &house, const QDate &date, QVector<std::pair<QString, int>> &&bills) const;
    bool insertHouseInsurance(const QString &house, const QDate &date, const int cost) const;
    bool updateHouseInsurance(const QString &house, const QDate &date, const int cost) const;
    bool insertHouseOtherExpense(const QString &house, QMap<QString, QString> &&item) const;

private:
    QSqlDatabase _db;
    QString _dbPath;
};

#endif // DATABASEMANAGER_H
