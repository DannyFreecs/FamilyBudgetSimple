#include "activitychild.h"
#include "ui_activitychild.h"

ActivityChild::ActivityChild(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityChild)
{
    ui->setupUi(this);

    ui->dateEditStudies->setDate(QDate::currentDate());
    ui->dateEditOther->setDate(QDate::currentDate());
}

ActivityChild::ActivityChild(const QString &child, QWidget *parent) : ActivityChild(parent)
{
    ui->labelChildName->setText(child);
}

ActivityChild::~ActivityChild()
{
    delete ui;
}
