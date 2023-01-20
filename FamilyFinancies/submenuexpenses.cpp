#include "submenuexpenses.h"
#include "ui_submenuexpenses.h"
#include <QCommandLinkButton>
#include "databasehandler.h"

SubMenuExpenses::SubMenuExpenses(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubMenuExpenses)
{
    ui->setupUi(this);
    initMenuItems();

}

SubMenuExpenses::~SubMenuExpenses()
{
    delete ui;
}

void SubMenuExpenses::initMenuItems()
{
    QVector<QString> vecHouses{DataBaseHandler::getDbManager()->getHouses()};
    for(const auto& text : vecHouses)
    {
        QPushButton *button = new QPushButton(text);
        button->setGeometry(QRect(30, 1, 177, 16));
        button->setStyleSheet("border: 0px; text-align: left; font: 12pt Algerian;");
        ui->verticalLayoutSubMenuHouses->addWidget(button);
        houseButtons.append(button);
    }

    QVector<QString> vecCars{DataBaseHandler::getDbManager()->getCars()};
    for(const auto& text : vecCars)
    {
        QPushButton *button = new QPushButton(text);
        button->setGeometry(QRect(30, 1, 177, 16));
        button->setStyleSheet("border: 0px; text-align: left; font: 12pt Algerian;");
        ui->verticalLayoutSubMenuCars->addWidget(button);
        carButtons.append(button);
    }

    QVector<QString> vecChildren{DataBaseHandler::getDbManager()->getChildren()};
    for(const auto& text : vecChildren)
    {
        QPushButton *button = new QPushButton(text);
        button->setGeometry(QRect(30, 1, 177, 16));
        button->setStyleSheet("border: 0px; text-align: left; font: 12pt Algerian;");
        ui->verticalLayoutSubMenuChildren->addWidget(button);
        childButtons.append(button);
    }
}
