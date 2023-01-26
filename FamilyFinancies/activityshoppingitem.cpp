#include "activityshoppingitem.h"
#include "ui_activityshoppingitem.h"
#include "databasehandler.h"

ActivityShoppingItem::ActivityShoppingItem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityShoppingItem)
{
    ui->setupUi(this);

    // set the date edit to current date
    ui->dateEdit->setDate(QDate::currentDate());
    // load the combo box with the categories from the database
    _categories = DataBaseHandler::getDbManager()->getShoppingCategories();
    ui->comboBoxCategories->addItems(_categories.values());
}

ActivityShoppingItem::~ActivityShoppingItem()
{
    delete ui;
}
