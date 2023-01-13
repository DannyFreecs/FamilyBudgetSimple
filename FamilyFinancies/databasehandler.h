#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QSqlDatabase>
#include <QSqlQuery>

class DataBaseHandler
{
public:
    DataBaseHandler();

    void connect()
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("..//Database//FamilyFinancies.db");

        if(db.open())
        {
            QSqlQuery q("SELECT * FROM Categories");
            while (q.next())
            {
                QString asd = q.value("SubCategory").toString();
            }
        }
        else
        {
            int x = 88;
        }
    }

private:
    QSqlDatabase db;
};

#endif // DATABASEHANDLER_H
