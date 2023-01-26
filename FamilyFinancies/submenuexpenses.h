#ifndef SUBMENUEXPENSES_H
#define SUBMENUEXPENSES_H

#include <QMainWindow>
#include <memory>
#include <QPushButton>
#include <QFrame>

namespace Ui {
class SubMenuExpenses;
}

class SubMenuExpenses : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubMenuExpenses(QWidget *parent = nullptr);
    ~SubMenuExpenses();

private:
    void loadMenuItemsFromDB();
    void setFramesToDefaultStyle();
    void setFrameToSelectedStyle(QFrame *frame);
    void setSubMenuButtonsToDefaultStyle();
    void setSubMenuButtonToSelectedStyle(QPushButton *button);

signals:
    void createActivityReceipt();
    void createActivityShoppingItem();

private slots:
    void on_menuButtonShopping_clicked();

    void on_menuButtonHouses_clicked();

    void on_menuButtonChildren_clicked();

    void on_menuButtonCars_clicked();

    void on_pushButtonShoppingItem_clicked();

    void on_pushButtonShoppingReceipt_clicked();

    void onSubMenuHouseButtonClicked();

    void onSubMenuChildButtonClicked();

    void onSubMenuCarButtonClicked();

    void on_menuButtonCredits_clicked();

    void on_menuButtonHealthCare_clicked();

    void on_menuButtonOther_clicked();

private:
    Ui::SubMenuExpenses *ui;
    QVector<QPushButton*> houseButtons;
    QVector<QPushButton*> carButtons;
    QVector<QPushButton*> childButtons;
    const QString subButtonDefaultStyle{R"X(border: 0px; font: 12pt "Algerian"; text-align: left;)X"};
    const QString subButtonSelectedStyle{R"X(border: 0px; font: 12pt "Algerian"; text-align: left; background-color: #296E85)X"};
};

#endif // SUBMENUEXPENSES_H
