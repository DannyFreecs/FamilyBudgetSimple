#include "activitychild.h"
#include <QMessageBox>
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
    const int lastCost = DataBaseHandler::getDbManager()->getChildStudyLastCost(ui->labelChildName->text());
    if (lastCost < 1) return;
    ui->spinBoxStudiesCost->setValue(lastCost);
}

void ActivityChild::on_pushButtonSaveStudies_clicked()
{
    const int cost = ui->spinBoxStudiesCost->valueFromText(ui->spinBoxStudiesCost->text());
    if (cost < 1)
    {
        QMessageBox::warning(nullptr, "Mentés", "Az összeg mezőben 0 Ft szerepel!");
        return;
    }

    if (DataBaseHandler::getDbManager()->insertChildStudyExpense(ui->labelChildName->text(), ui->dateEditStudies->date(), cost))
    {
        QMessageBox::information(nullptr, "Mentés", "Sikeres mentés!");
    }
    else
    {
        QMessageBox::critical(nullptr, "Mentés", "A mentés során hiba történt!");
    }
}

