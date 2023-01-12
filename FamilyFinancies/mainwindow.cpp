#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QBrush>
#include <QColor>
#include <QRgb>
#include <QTabBar>
#include <QToolBar>
#include "submenuwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SubMenuWindow *submenu = new SubMenuWindow();
    ui->mdiAreaSubMenu->addSubWindow(submenu, Qt::FramelessWindowHint);
    submenu->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

