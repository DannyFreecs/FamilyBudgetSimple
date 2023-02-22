#include "activitychild.h"
#include <QMessageBox>
#include "ui_activitychild.h"
#include "databasehandler.h"
#include "yearmonthchooser.h"

ActivityChild::ActivityChild(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityChild)
{
    ui->setupUi(this);

    ui->dateEditStudies->setDate(QDate::currentDate());
    ui->dateEditStudies->setCalendarWidget(new YearMonthChooser);
    ui->dateEditOther->setDate(QDate::currentDate());
}

ActivityChild::ActivityChild(const QString &child, QWidget *parent) : ActivityChild(parent)
{
    ui->labelChildName->setText(child);
    initStudyCostField();

    connect(ui->dateEditStudies, &QDateEdit::dateChanged, this, &ActivityChild::checkStudyExpenseExistence);
    connect(ui->spinBoxStudiesCost, &QAbstractSpinBox::editingFinished, this, &ActivityChild::checkStudyExpenseExistence);
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

void ActivityChild::checkStudyExpenseExistence() const
{
    ui->labelWarnStudyCost->setHidden(!(DataBaseHandler::getDbManager()->checkChildStudyExpenseExistence(ui->labelChildName->text(), ui->dateEditStudies->date())
                                  && ui->spinBoxStudiesCost->valueFromText(ui->spinBoxStudiesCost->text()) > 0));
}

void ActivityChild::on_pushButtonSaveStudies_clicked()
{
    const int cost = ui->spinBoxStudiesCost->valueFromText(ui->spinBoxStudiesCost->text());
    if (cost < 1)
    {
        QMessageBox::warning(nullptr, "Mentés", "Az összeg mezőben 0 Ft szerepel!");
        return;
    }

    DataBaseHandler::getDbManager()->insertChildExpense(ui->labelChildName->text(), ui->dateEditStudies->date(), cost, "Tanulmány")
            ? QMessageBox::information(nullptr, "Mentés", "Sikeres mentés!")
            : QMessageBox::critical(nullptr, "Mentés", "A mentés során hiba történt!");
}

void ActivityChild::on_pushButtonSaveOther_clicked()
{
    const int cost = ui->spinBoxOtherCost->valueFromText(ui->spinBoxOtherCost->text());
    if (cost < 1)
    {
        QMessageBox::warning(nullptr, "Mentés", "Az összeg mezőben 0 Ft szerepel!");
        return;
    }

    DataBaseHandler::getDbManager()->insertChildExpense(ui->labelChildName->text(), ui->dateEditOther->date(), cost, "Egyéb", ui->lineEditComment->text())
            ? QMessageBox::information(nullptr, "Mentés", "Sikeres mentés!")
            : QMessageBox::critical(nullptr, "Mentés", "A mentés során hiba történt!");
}

