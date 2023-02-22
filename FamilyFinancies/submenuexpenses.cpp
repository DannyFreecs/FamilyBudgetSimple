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
        button->setStyleSheet("border: 0px; text-align: left; font: 12pt Algerian;");
        button->setHidden(true);
        connect(button, &QPushButton::clicked, this, &SubMenuExpenses::onSubMenuHouseButtonClicked);
        ui->verticalLayoutSubMenuHouses->addWidget(button);
        houseButtons.append(button);
    }

    QVector<QString> vecCars{DataBaseHandler::getDbManager()->getCars()};
    for(const auto& text : vecCars)
    {
        QPushButton *button = new QPushButton(text);
        button->setGeometry(QRect(30, 1, 177, 16));
        button->setStyleSheet("border: 0px; text-align: left; font: 12pt Algerian;");
        button->setHidden(true);
        connect(button, &QPushButton::clicked, this, &SubMenuExpenses::onSubMenuCarButtonClicked);
        ui->verticalLayoutSubMenuCars->addWidget(button);
        carButtons.append(button);
    }

    QVector<QString> vecChildren{DataBaseHandler::getDbManager()->getChildren()};
    for(const auto& text : vecChildren)
    {
        QPushButton *button = new QPushButton(text);
        button->setGeometry(QRect(30, 1, 177, 16));
        button->setStyleSheet("border: 0px; text-align: left; font: 12pt Algerian;");
        button->setHidden(true);
        connect(button, &QPushButton::clicked, this, &SubMenuExpenses::onSubMenuChildButtonClicked);
        ui->verticalLayoutSubMenuChildren->addWidget(button);
        childButtons.append(button);
    }
}

void SubMenuExpenses::setFramesToDefaultStyle()
{
    QString defaultStyle("background-color: rgb(173, 216, 230); border: 0px;");
    ui->frameCars->setStyleSheet(defaultStyle);
    ui->frameChildren->setStyleSheet(defaultStyle);
    ui->frameHouses->setStyleSheet(defaultStyle);
    ui->frameOthers->setStyleSheet(defaultStyle);
    ui->frameShopping->setStyleSheet(defaultStyle);
    ui->frameHealthCare->setStyleSheet(defaultStyle);
    ui->frameCredits->setStyleSheet(defaultStyle);
    ui->framePhone->setStyleSheet(defaultStyle);
}

void SubMenuExpenses::setFrameToSelectedStyle(QFrame *frame)
{
    frame->setStyleSheet("background-color: #67B7D1; border: 0px;");
}

void SubMenuExpenses::setSubMenuButtonsToDefaultStyle()
{
    ui->pushButtonShoppingItem->setStyleSheet(subButtonDefaultStyle);
    ui->pushButtonShoppingReceipt->setStyleSheet(subButtonDefaultStyle);

    for(auto& button : houseButtons) button->setStyleSheet(subButtonDefaultStyle);
    for(auto& button : childButtons) button->setStyleSheet(subButtonDefaultStyle);
    for(auto& button : carButtons)   button->setStyleSheet(subButtonDefaultStyle);
}

void SubMenuExpenses::setSubMenuButtonToSelectedStyle(QPushButton *button)
{
    button->setStyleSheet(subButtonSelectedStyle);
}

void SubMenuExpenses::on_menuButtonShopping_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameShopping);
    ui->menuButtonShopping->setIcon(QIcon(ui->pushButtonShoppingReceipt->isHidden() ? ":/icons/Resources/arrow-down-icon.png" : ":/icons/Resources/arrow-right-icon.png"));
    ui->pushButtonShoppingReceipt->setHidden(!ui->pushButtonShoppingReceipt->isHidden());
    ui->pushButtonShoppingItem->setHidden(!ui->pushButtonShoppingItem->isHidden());
}


void SubMenuExpenses::on_menuButtonHouses_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameHouses);
    ui->menuButtonHouses->setIcon(QIcon(houseButtons[0]->isHidden() ? ":/icons/Resources/arrow-down-icon.png" : ":/icons/Resources/arrow-right-icon.png"));

    for (auto button : houseButtons) button->setHidden(!button->isHidden());
}


void SubMenuExpenses::on_menuButtonChildren_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameChildren);
    ui->menuButtonChildren->setIcon(QIcon(childButtons[0]->isHidden() ? ":/icons/Resources/arrow-down-icon.png" : ":/icons/Resources/arrow-right-icon.png"));

    for (auto button : childButtons) button->setHidden(!button->isHidden());
}


void SubMenuExpenses::on_menuButtonCars_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameCars);
    ui->menuButtonCars->setIcon(QIcon(carButtons[0]->isHidden() ? ":/icons/Resources/arrow-down-icon.png" : ":/icons/Resources/arrow-right-icon.png"));

    for (auto button : carButtons) button->setHidden(!button->isHidden());
}

void SubMenuExpenses::on_pushButtonShoppingReceipt_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameShopping);
    setSubMenuButtonsToDefaultStyle();
    setSubMenuButtonToSelectedStyle(ui->pushButtonShoppingReceipt);

    emit sendCreateActivityReceipt();
}

void SubMenuExpenses::onSubMenuHouseButtonClicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameHouses);
    setSubMenuButtonsToDefaultStyle();
    setSubMenuButtonToSelectedStyle(qobject_cast<QPushButton*>(QObject::sender()));

    emit sendCreateActivityHouse(qobject_cast<QPushButton*>(QObject::sender())->text());
}

void SubMenuExpenses::onSubMenuChildButtonClicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameChildren);
    setSubMenuButtonsToDefaultStyle();
    setSubMenuButtonToSelectedStyle(qobject_cast<QPushButton*>(QObject::sender()));

    emit sendCreateActivityChild(qobject_cast<QPushButton*>(QObject::sender())->text());
}

void SubMenuExpenses::onSubMenuCarButtonClicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameCars);
    setSubMenuButtonsToDefaultStyle();
    setSubMenuButtonToSelectedStyle(qobject_cast<QPushButton*>(QObject::sender()));
}

void SubMenuExpenses::on_pushButtonShoppingItem_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameShopping);
    setSubMenuButtonsToDefaultStyle();
    setSubMenuButtonToSelectedStyle(ui->pushButtonShoppingItem);

    emit sendCreateActivityShoppingItem();
}

void SubMenuExpenses::on_menuButtonCredits_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameCredits);
    setSubMenuButtonsToDefaultStyle();
}


void SubMenuExpenses::on_menuButtonHealthCare_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameHealthCare);
    setSubMenuButtonsToDefaultStyle();

    emit sendCreateActivityMedical();
}


void SubMenuExpenses::on_menuButtonOther_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->frameOthers);
    setSubMenuButtonsToDefaultStyle();
}


void SubMenuExpenses::on_menuButtonPhone_clicked()
{
    setFramesToDefaultStyle();
    setFrameToSelectedStyle(ui->framePhone);
    setSubMenuButtonsToDefaultStyle();
}

