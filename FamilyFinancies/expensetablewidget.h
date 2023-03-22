#ifndef EXPENSETABLEWIDGET_H
#define EXPENSETABLEWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <functional>

namespace Ui {
class ExpenseTableWidget;
}

class ExpenseTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExpenseTableWidget(QWidget *parent = nullptr);
    ~ExpenseTableWidget();

    QSqlRelationalTableModel *model;
private:
    Ui::ExpenseTableWidget *ui;
};

#endif // EXPENSETABLEWIDGET_H
