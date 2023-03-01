#include "activityshoppingitem.h"
#include <QMessageBox>
#include "ui_activityshoppingitem.h"
#include "databasehandler.h"

ActivityShoppingItem::ActivityShoppingItem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityShoppingItem)
{
    ui->setupUi(this);

    // set the date edit to current date
    ui->dateEdit->setDate(QDate::currentDate());
    // load the combo box with the categories from the database
    _categories = DataBaseHandler::getDbManager()->getShoppingCategories();
    ui->comboBoxCategories->addItems(_categories.values());
}

ActivityShoppingItem::~ActivityShoppingItem()
{
    delete ui;
}

void ActivityShoppingItem::on_pushButtonSave_clicked()
{
    const int cost = ui->spinBoxCostItem->valueFromText(ui->spinBoxCostItem->text());
    if (cost < 1)
    {
        QMessageBox::warning(nullptr, "Mentés", "Az összeg mezőben 0 Ft szerepel!");
        return;
    }

    if (DataBaseHandler::getDbManager()->insertShoppingItem(cost, ui->dateEdit->date(), ui->comboBoxCategories->currentText(), ui->textEditComment->toPlainText()))
    {
        ui->spinBoxCostItem->cleanText();
        ui->textEditComment->clear();
        QMessageBox::information(nullptr, "Mentés", "Sikeres mentés!");
    }
    else
    {
        QMessageBox::critical(nullptr, "Mentés", "A mentés során hiba történt!");
    }
}

