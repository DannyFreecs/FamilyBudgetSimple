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
    int getHouseId(QString &&address) const;
    bool checkHouseExpenseExistence(QString &&house, const QDate &when, QString &&type, QString &&subType = "") const;
    bool checkChildStudyExpenseExistence(QString &&child, QDate &&when) const;
    QVector<QString> getCars() const;
    QVector<QString> getChildren() const;
    QMap<QString, QString> getShoppingCategories() const;
    QMap<QString, int> getHouseLastFixCosts(QString &&address) const;
    int getChildId(const QString &child) const;
    int getChildStudyLastCost(const QString &child) const;

    bool insertShoppingReceipt(QVector<QVector<QString>> &&shoppingData) const;
    bool insertShoppingItem(const int cost, QDate &&date, QString &&category, QString &&comment) const;
    bool insertHouseBills(QString &&house, const QDate &date, QVector<std::pair<QString, int>> &&bills) const;
    bool updateHouseBills(QString &&house, const QDate &date, QVector<std::pair<QString, int>> &&bills) const;
    bool insertHouseInsurance(QString &&house, const QDate &date, const int cost) const;
    bool updateHouseInsurance(QString &&house, const QDate &date, const int cost) const;
    bool insertHouseOtherExpense(QString &&house, QMap<QString, QString> &&item) const;
    bool insertChildExpense(QString &&child, QDate &&date, const int cost, QString &&category, QString &&comment="") const;
    bool insertMedicalExpense(const int cost, QDate &&date, QString &&comment) const;
    bool insertOtherExpense(const int cost, QDate &&date, QString &&comment) const;

private:
    QSqlDatabase _db;
    QString _dbPath;
};

#endif // DATABASEMANAGER_H
