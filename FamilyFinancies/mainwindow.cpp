#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QBrush>
#include <QColor>
#include <QRgb>
#include <QTabBar>
#include <QToolBar>
#include "databasehandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    subMenuExpenses = std::make_unique<SubMenuExpenses>();

    ui->mdiAreaSubMenu->addSubWindow(subMenuExpenses.get(), Qt::FramelessWindowHint);
    subMenuExpenses->showMaximized();

    //DataBaseHandler handler;
    //handler.connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

