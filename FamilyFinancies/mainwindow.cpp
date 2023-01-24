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

    _subMenuExpenses = std::make_unique<SubMenuExpenses>();
    ui->mdiAreaSubMenu->addSubWindow(_subMenuExpenses.get(), Qt::FramelessWindowHint);
    _subMenuExpenses->showMaximized();

    ActivityReceipt *ar = new ActivityReceipt();
    ui->mdiAreaActivity->addSubWindow(ar, Qt::FramelessWindowHint);
    ar->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

