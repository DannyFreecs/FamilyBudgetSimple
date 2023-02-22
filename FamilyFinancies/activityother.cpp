#include "activityother.h"
#include "ui_activityother.h"

ActivityOther::ActivityOther(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityOther)
{
    ui->setupUi(this);
}

ActivityOther::~ActivityOther()
{
    delete ui;
}
