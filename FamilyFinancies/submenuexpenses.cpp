#include "submenuexpenses.h"
#include "ui_submenuexpenses.h"
#include <QCommandLinkButton>

SubMenuExpenses::SubMenuExpenses(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubMenuExpenses)
{
    ui->setupUi(this);
    setStyleSheet("background-color: rgb(221, 234, 240); border: 2px solid black;");
    //ui->centralwidget->setStyleSheet("border: 0px");
    //ui->menuButtonCars->setal
//    ui->pushButtonShoppingItem->setVisible(false);
//    ui->pushButtonShoppingItem_2->setVisible(false);
//    ui->pushButtonShoppingItem_3->setVisible(false);
//    ui->pushButtonShoppingReceipt->setVisible(false);
//    ui->pushButtonShoppingReceipt_2->setVisible(false);
//    ui->pushButtonShoppingReceipt_3->setVisible(false);

//    ui->verticalLayoutMenuShopping->removeItem(ui->verticalLayoutSubMenuShopping);
//    ui->verticalLayoutMenuCars->removeItem(ui->verticalLayoutSubMenuCars);
//    ui->verticalLayoutMenuHouses->removeItem(ui->verticalLayoutSubMenuHouses);
}

SubMenuExpenses::~SubMenuExpenses()
{
    delete ui;
}
