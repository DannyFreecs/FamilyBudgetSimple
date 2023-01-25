#include "submenuexpenses.h"
#include "ui_submenuexpenses.h"
#include <QCommandLinkButton>
#include "databasehandler.h"

SubMenuExpenses::SubMenuExpenses(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubMenuExpenses)
{
    ui->setupUi(this);
    ui->pushButtonShoppingReceipt->setHidden(true);
    ui->pushButtonShoppingItem->setHidden(true);
    loadMenuItemsFromDB();

}

SubMenuExpenses::~SubMenuExpenses()
{
    delete ui;
}

void SubMenuExpenses::loadMenuItemsFromDB()
{
    QVector<QString> vecHouses{DataBaseHandler::getDbManager()->getHouses()};
    for(const auto& text : vecHouses)
    {
        QPushButton *button = new QPushButton(text);
        button->setGeometry(QRect(30, 1, 177, 16));
        button->setStyleSheet("border: 0px; text-align: left; font: 12pt Algerian; background-color: rgb(190, 229, 240);");
        button->setHidden(true);
        ui->verticalLayoutSubMenuHouses->addWidget(button);
        houseButtons.append(button);
    }

    QVector<QString> vecCars{DataBaseHandler::getDbManager()->getCars()};
    for(const auto& text : vecCars)
    {
        QPushButton *button = new QPushButton(text);
        button->setGeometry(QRect(30, 1, 177, 16));
        button->setStyleSheet("border: 0px; text-align: left; font: 12pt Algerian; background-color: rgb(190, 229, 240);");
        button->setHidden(true);
        ui->verticalLayoutSubMenuCars->addWidget(button);
        carButtons.append(button);
    }

    QVector<QString> vecChildren{DataBaseHandler::getDbManager()->getChildren()};
    for(const auto& text : vecChildren)
    {
        QPushButton *button = new QPushButton(text);
        button->setGeometry(QRect(30, 1, 177, 16));
        button->setStyleSheet("border: 0px; text-align: left; font: 12pt Algerian; background-color: rgb(190, 229, 240);");
        button->setHidden(true);
        ui->verticalLayoutSubMenuChildren->addWidget(button);
        childButtons.append(button);
    }
}

void SubMenuExpenses::on_menuButtonShopping_clicked()
{
    ui->menuButtonShopping->setIcon(QIcon(ui->pushButtonShoppingReceipt->isHidden() ? ":/icons/Resources/arrow-down-icon.png"
                                                                                    : ":/icons/Resources/arrow-right-icon.png"));
    ui->pushButtonShoppingReceipt->setHidden(!ui->pushButtonShoppingReceipt->isHidden());
    ui->pushButtonShoppingItem->setHidden(!ui->pushButtonShoppingItem->isHidden());
}


void SubMenuExpenses::on_menuButtonHouses_clicked()
{
    ui->menuButtonHouses->setIcon(QIcon(houseButtons[0]->isHidden() ? ":/icons/Resources/arrow-down-icon.png"
                                                                    : ":/icons/Resources/arrow-right-icon.png"));

    for (auto button : houseButtons) button->setHidden(!button->isHidden());
}


void SubMenuExpenses::on_menuButtonChildren_clicked()
{
    ui->menuButtonChildren->setIcon(QIcon(childButtons[0]->isHidden() ? ":/icons/Resources/arrow-down-icon.png"
                                                                      : ":/icons/Resources/arrow-right-icon.png"));

    for (auto button : childButtons) button->setHidden(!button->isHidden());
}


void SubMenuExpenses::on_menuButtonCars_clicked()
{
    ui->menuButtonCars->setIcon(QIcon(carButtons[0]->isHidden() ? ":/icons/Resources/arrow-down-icon.png"
                                                                : ":/icons/Resources/arrow-right-icon.png"));

    for (auto button : carButtons) button->setHidden(!button->isHidden());
}


void SubMenuExpenses::on_pushButtonShoppingItem_clicked()
{
    emit createActivityShoppingItem();
}

