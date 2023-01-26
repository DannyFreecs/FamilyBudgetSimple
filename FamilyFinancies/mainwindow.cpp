#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QBrush>
#include <QColor>
#include <QRgb>
#include <QTabBar>
#include <QToolBar>
#include <QPixmap>
#include <QPalette>
#include <QAction>
#include <QWidgetAction>
#include "databasehandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the static database handler!!!
    DataBaseHandler::initDbManager("..//Database//FamilyFinancies.db");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMenuButtonsToDefaultStyle()
{
    QString defaultStyle("background-color: rgb(190, 229, 240); border: 2px solid black;");
    ui->menuButtonExpenses->setStyleSheet(defaultStyle);
    ui->menuButtonIncomes->setStyleSheet(defaultStyle);
    ui->menuButtonStats->setStyleSheet(defaultStyle);
    ui->menuButtonOptions->setStyleSheet(defaultStyle);
}

void MainWindow::setMenuButtonsSelectedStyle(QPushButton *button)
{
    button->setStyleSheet("background-color: #67B7D1; border: 2px solid black;");
}

void MainWindow::on_createActivityReceipt()
{
    on_actionAddBlock_triggered();
}

void MainWindow::on_createActivityShoppingItem()
{
    on_actionAddItem_triggered();
}


void MainWindow::on_menuButtonExpenses_clicked()
{
    setMenuButtonsToDefaultStyle();
    setMenuButtonsSelectedStyle(ui->menuButtonExpenses);
    _subMenuExpenses = std::make_unique<SubMenuExpenses>();
    ui->mdiAreaSubMenu->closeActiveSubWindow();
    ui->mdiAreaSubMenu->addSubWindow(_subMenuExpenses.get(), Qt::FramelessWindowHint);
    _subMenuExpenses->showMaximized();
    connect(_subMenuExpenses.get(), &SubMenuExpenses::createActivityReceipt, this, &MainWindow::on_createActivityReceipt);
    connect(_subMenuExpenses.get(), &SubMenuExpenses::createActivityShoppingItem, this, &MainWindow::on_createActivityShoppingItem);
}


void MainWindow::on_actionAddBlock_triggered()
{
    _activityReceipt.release();
    _activityReceipt = std::make_unique<ActivityReceipt>();
    ui->mdiAreaActivity->closeAllSubWindows();
    ui->mdiAreaActivity->addSubWindow(_activityReceipt.get(), Qt::FramelessWindowHint);
    _activityReceipt->showMaximized();
}


void MainWindow::on_actionAddItem_triggered()
{
    _activityShoppingItem.release();
    _activityShoppingItem = std::make_unique<ActivityShoppingItem>();
    ui->mdiAreaActivity->closeAllSubWindows();
    ui->mdiAreaActivity->addSubWindow(_activityShoppingItem.get(), Qt::FramelessWindowHint);
    _activityShoppingItem->showMaximized();
}

