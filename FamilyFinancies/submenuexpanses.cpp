#include "submenuexpanses.h"
#include "ui_submenuexpanses.h"

SubMenuExpanses::SubMenuExpanses(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubMenuExpanses)
{
    ui->setupUi(this);
}

SubMenuExpanses::~SubMenuExpanses()
{
    delete ui;
}
