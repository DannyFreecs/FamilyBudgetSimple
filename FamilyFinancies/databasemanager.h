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
    QVector<QString> getHouses() const;
    int getHouseId(const QString &address) const;
    int getHouseExpenseId(QString &&subCategory, QString &&subSubCategory = "") const;
    bool checkHouseExpenseExistence(const int houseId, const QDate &when, QString &&type, QString &&subType = "") const;
    QVector<QString> getCars() const;
    QVector<QString> getChildren() const;
    QMap<QString, QString> getShoppingCategories() const;
    QMap<QString, int> getHouseFixCosts() const;


    bool insertShoppingReceipt(QVector<QVector<QString>> &&shoppingData) const;
    bool insertShoppingItem(QVector<QString> &&itemData) const;
    bool insertHouseBills(const QString &house, const QDate &date, QMap<QString, int> &&bills) const;

private:
    QSqlDatabase _db;
    QString _dbPath;
};

#endif // DATABASEMANAGER_H
