#include "activityshoppingitem.h"
#include "ui_activityshoppingitem.h"

ActivityShoppingItem::ActivityShoppingItem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityShoppingItem)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
}

ActivityShoppingItem::~ActivityShoppingItem()
{
    delete ui;
}
