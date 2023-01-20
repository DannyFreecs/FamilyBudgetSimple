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

private:
    void initMenuItems();

private:
    Ui::SubMenuExpenses *ui;
    QVector<QPushButton*> houseButtons;
    QVector<QPushButton*> carButtons;
    QVector<QPushButton*> childButtons;
};

#endif // SUBMENUEXPENSES_H
