#include "submenuwindow.h"
#include "ui_submenuwindow.h"

SubMenuWindow::SubMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubMenuWindow)
{
    ui->setupUi(this);
}

SubMenuWindow::~SubMenuWindow()
{
    delete ui;
}
