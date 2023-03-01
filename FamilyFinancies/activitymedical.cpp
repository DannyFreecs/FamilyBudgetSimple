#include "activitymedical.h"
#include "ui_activitymedical.h"
#include <QMessageBox>
#include "databasehandler.h"
#include <QTabBar>

ActivityMedical::ActivityMedical(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityMedical)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    auto tabBar = ui->tabWidget->findChild<QTabBar*>();
    auto asd = tabBar->findChildren<QWidget*>();

    int x = 7;
}

ActivityMedical::~ActivityMedical()
{
    delete ui;
}

void ActivityMedical::on_pushButtonSave_clicked()
{
    const int cost = ui->spinBoxCost->valueFromText(ui->spinBoxCost->text());
    if (cost < 1)
    {
        QMessageBox::warning(nullptr, "Mentés", "Az összeg mezőben 0 Ft szerepel!");
        return;
    }

    DataBaseHandler::getDbManager()->insertMedicalExpense(cost, ui->dateEdit->date(), ui->textEditComment->toPlainText())
            ? QMessageBox::information(nullptr, "Mentés", "Sikeres mentés!")
            : QMessageBox::critical(nullptr, "Mentés", "Sikertelen mentés!");
}

