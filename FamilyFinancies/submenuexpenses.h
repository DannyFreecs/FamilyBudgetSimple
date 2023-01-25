#ifndef SUBMENUEXPENSES_H
#define SUBMENUEXPENSES_H

#include <QMainWindow>
#include <memory>
#include <QPushButton>

namespace Ui {
class SubMenuExpenses;
}

class SubMenuExpenses : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubMenuExpenses(QWidget *parent = nullptr);
    ~SubMenuExpenses();

signals:
    void createActivityShoppingItem();

private slots:
    void on_menuButtonShopping_clicked();

    void on_menuButtonHouses_clicked();

    void on_menuButtonChildren_clicked();

    void on_menuButtonCars_clicked();

    void on_pushButtonShoppingItem_clicked();

private:
    void loadMenuItemsFromDB();

private:
    Ui::SubMenuExpenses *ui;
    QVector<QPushButton*> houseButtons;
    QVector<QPushButton*> carButtons;
    QVector<QPushButton*> childButtons;
};

#endif // SUBMENUEXPENSES_H
