#ifndef SUBMENUEXPENSES_H
#define SUBMENUEXPENSES_H

#include <QMainWindow>

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
    Ui::SubMenuExpenses *ui;
};

#endif // SUBMENUEXPENSES_H
