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
    QMap<QString, QString> getShoppingCategories();
    QMap<QString, int> getHouseFixCosts();


    bool insertShoppingReceipt(QVector<QVector<QString>> &&shoppingData);
    bool insertShoppingItem(QVector<QString> &&itemData);
    bool insertHouseBills(const QString &house, const QDate &date, QMap<QString, int> &&bills);

private:
    QSqlDatabase _db;
    QString _dbPath;
};

#endif // DATABASEMANAGER_H
