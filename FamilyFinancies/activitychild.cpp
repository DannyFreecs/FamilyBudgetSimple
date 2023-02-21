#include "activitychild.h"
#include "ui_activitychild.h"
#include "databasehandler.h"

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
    initStudyCostField();
}

ActivityChild::~ActivityChild()
{
    delete ui;
}

void ActivityChild::initStudyCostField() const
{
    int lastCost = DataBaseHandler::getDbManager()->getChildStudyLastCost(ui->labelChildName->text());
    if (lastCost < 1) return;
    ui->spinBoxStudiesCost->setValue(lastCost);
}

void ActivityChild::on_pushButtonSaveStudies_clicked()
{

}

