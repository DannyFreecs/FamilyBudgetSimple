#include "activitymedical.h"
#include "ui_activitymedical.h"

ActivityMedical::ActivityMedical(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityMedical)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

ActivityMedical::~ActivityMedical()
{
    delete ui;
}
