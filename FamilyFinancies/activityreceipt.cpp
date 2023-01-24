#include "activityreceipt.h"
#include "ui_activityreceipt.h"
#include "databasehandler.h"

ActivityReceipt::ActivityReceipt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityReceipt)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());

    receiptModel = std::make_unique<QStandardItemModel>();
    receiptModel->setHorizontalHeaderItem(0, new QStandardItem("Összeg"));
    receiptModel->setHorizontalHeaderItem(1, new QStandardItem("Kategória"));
    receiptModel->setHorizontalHeaderItem(2, new QStandardItem("Dátum"));
    receiptModel->setHorizontalHeaderItem(3, new QStandardItem("Leírás"));

    ui->tableView->setModel(receiptModel.get());
    ui->comboBoxCategories->addItems(DataBaseHandler::getDbManager()->getShoppingCategories());
}

ActivityReceipt::~ActivityReceipt()
{
    delete ui;
}
