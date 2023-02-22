#include "activitymedical.h"
#include "ui_activitymedical.h"

ActivityMedical::ActivityMedical(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityMedical)
{
    ui->setupUi(this);
}

ActivityMedical::~ActivityMedical()
{
    delete ui;
}
