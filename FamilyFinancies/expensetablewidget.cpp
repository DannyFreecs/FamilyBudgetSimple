#include "expensetablewidget.h"
#include "ui_expensetablewidget.h"
#include "databasehandler.h"

ExpenseTableWidget::ExpenseTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpenseTableWidget)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel();
    model->setTable("Expenses");
    model->select();
    ui->tableView->setModel(model);
}

ExpenseTableWidget::~ExpenseTableWidget()
{
    delete ui;
}
