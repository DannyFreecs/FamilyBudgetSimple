#include "activityother.h"
#include "ui_activityother.h"
#include "databasehandler.h"
#include <QMessageBox>

ActivityOther::ActivityOther(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityOther)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

ActivityOther::~ActivityOther()
{
    delete ui;
}

void ActivityOther::on_pushButtonSave_clicked()
{
    const int cost = ui->spinBoxCost->valueFromText(ui->spinBoxCost->text());
    if (cost < 1)
    {
        QMessageBox::warning(nullptr, "Mentés", "Az összeg mezőben 0 Ft szerepel!");
        return;
    }

    DataBaseHandler::getDbManager()->insertOtherExpense(cost, ui->dateEdit->date(), ui->textEditComment->toPlainText())
            ? QMessageBox::information(nullptr, "Mentés", "Sikeres mentés!")
            : QMessageBox::critical(nullptr, "Mentés", "Sikertelen mentés!");
}

