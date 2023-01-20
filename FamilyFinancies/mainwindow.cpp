#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QBrush>
#include <QColor>
#include <QRgb>
#include <QTabBar>
#include <QToolBar>
#include <QPixmap>
#include <QPalette>
#include "databasehandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DataBaseHandler::initDbManager("..//Database//FamilyFinancies.db");

    _subMenuExpenses = std::make_unique<SubMenuExpenses>();
    ui->mdiAreaSubMenu->addSubWindow(_subMenuExpenses.get(), Qt::FramelessWindowHint);
    _subMenuExpenses->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

