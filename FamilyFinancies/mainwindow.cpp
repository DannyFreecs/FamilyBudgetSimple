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

void MainWindow::releaseActivites()
{
    _activityReceipt.release();
    _activityShoppingItem.release();
    _activityHouse.release();
    _activityChild.release();
    _activityMedical.release();
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

void MainWindow::onCreateActivityReceipt()
{
    on_actionAddReceipt_triggered();
}

void MainWindow::onCreateActivityShoppingItem()
{
    on_actionAddItem_triggered();
}

void MainWindow::onCreateActivityHouse(const QString &house)
{
    /******RELEASE******/
    releaseActivites();
    /************/

    _activityHouse = std::make_unique<ActivityHouse>(house);
    ui->mdiAreaActivity->closeAllSubWindows();
    ui->mdiAreaActivity->addSubWindow(_activityHouse.get(), Qt::FramelessWindowHint);
    _activityHouse->showMaximized();
}

void MainWindow::onCreateActivityChild(const QString &child)
{
    /******RELEASE******/
    releaseActivites();
    /************/

    _activityChild = std::make_unique<ActivityChild>(child);
    ui->mdiAreaActivity->closeAllSubWindows();
    ui->mdiAreaActivity->addSubWindow(_activityChild.get(), Qt::FramelessWindowHint);
    _activityChild->showMaximized();
}

void MainWindow::onCreateActivityMedical()
{
    /******RELEASE******/
    releaseActivites();
    /************/

    _activityMedical = std::make_unique<ActivityMedical>();
    ui->mdiAreaActivity->closeAllSubWindows();
    ui->mdiAreaActivity->addSubWindow(_activityMedical.get(), Qt::FramelessWindowHint);
    _activityMedical->showMaximized();
}

void MainWindow::on_menuButtonExpenses_clicked()
{
    setMenuButtonsToDefaultStyle();
    setMenuButtonsSelectedStyle(ui->menuButtonExpenses);
    _subMenuExpenses = std::make_unique<SubMenuExpenses>();
    ui->mdiAreaSubMenu->closeActiveSubWindow();
    ui->mdiAreaSubMenu->addSubWindow(_subMenuExpenses.get(), Qt::FramelessWindowHint);
    _subMenuExpenses->showMaximized();
    connect(_subMenuExpenses.get(), &SubMenuExpenses::sendCreateActivityReceipt, this, &MainWindow::onCreateActivityReceipt);
    connect(_subMenuExpenses.get(), &SubMenuExpenses::sendCreateActivityShoppingItem, this, &MainWindow::onCreateActivityShoppingItem);
    connect(_subMenuExpenses.get(), &SubMenuExpenses::sendCreateActivityHouse, this, &MainWindow::onCreateActivityHouse);
    connect(_subMenuExpenses.get(), &SubMenuExpenses::sendCreateActivityChild, this, &MainWindow::onCreateActivityChild);
    connect(_subMenuExpenses.get(), &SubMenuExpenses::sendCreateActivityMedical, this, &MainWindow::onCreateActivityMedical);
}

void MainWindow::on_actionAddReceipt_triggered()
{
    /******RELEASE******/
    releaseActivites();
    /************/

    _activityReceipt = std::make_unique<ActivityReceipt>();
    ui->mdiAreaActivity->closeAllSubWindows();
    ui->mdiAreaActivity->addSubWindow(_activityReceipt.get(), Qt::FramelessWindowHint);
    _activityReceipt->showMaximized();
}

void MainWindow::on_actionAddItem_triggered()
{
    /******RELEASE******/
    releaseActivites();
    /************/

    _activityShoppingItem = std::make_unique<ActivityShoppingItem>();
    ui->mdiAreaActivity->closeAllSubWindows();
    ui->mdiAreaActivity->addSubWindow(_activityShoppingItem.get(), Qt::FramelessWindowHint);
    _activityShoppingItem->showMaximized();
}




