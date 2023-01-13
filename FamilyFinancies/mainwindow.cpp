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
    subMenuExpanses = std::make_unique<SubMenuExpanses>();
    ui->mdiAreaSubMenu->addSubWindow(subMenuExpanses.get(), Qt::FramelessWindowHint);
    subMenuExpanses->showMaximized();

    DataBaseHandler handler;
    handler.connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

