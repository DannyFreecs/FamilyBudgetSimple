#include "activityreceipt.h"
#include "ui_activityreceipt.h"
#include "databasehandler.h"
#include <QRegularExpression>
#include <QMessageBox>

ActivityReceipt::ActivityReceipt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityReceipt)
{
    ui->setupUi(this);

    // set the date edit to current date
    ui->dateEdit->setDate(QDate::currentDate());
    // load the combo box with the categories from the database
    _categories = DataBaseHandler::getDbManager()->getShoppingCategories();
    ui->comboBoxCategories->addItems(_categories.values());
    initTableView();
}

ActivityReceipt::~ActivityReceipt()
{
    delete ui;
}

void ActivityReceipt::initTableView()
{
    _receiptModel = std::make_unique<QStandardItemModel>();
    _receiptModel->setHorizontalHeaderItem(0, new QStandardItem("Összeg"));
    _receiptModel->setHorizontalHeaderItem(1, new QStandardItem("Kategória"));
    _receiptModel->setHorizontalHeaderItem(2, new QStandardItem("Dátum"));
    _receiptModel->setHorizontalHeaderItem(3, new QStandardItem("Leírás"));

    ui->tableView->setModel(_receiptModel.get());
}

bool ActivityReceipt::validateCost()
{
    if (!ui->lineEditCostItem->text().toInt())
    {
        QMessageBox::warning(nullptr, "Hiba", "Összeg mezőben nem szám szerepel!");
        return false;
    }

    if (ui->lineEditCostItem->text().toInt() < 1)
    {
        QMessageBox::warning(nullptr, "Hiba", "Összeg mezőben nem 0-nál nagyobb szám szerepel!");
        return false;
    }

    return true;
}

void ActivityReceipt::on_pushButtonAddItem_clicked()
{
    if (!validateCost())
    {
        return;
    }
    // create row items and add the row to the item model
    QList<QStandardItem*> row;
    QStandardItem *cost = new QStandardItem(ui->lineEditCostItem->text());
    cost->setTextAlignment(Qt::AlignCenter);
    QStandardItem *category = new QStandardItem(ui->comboBoxCategories->currentText());
    category->setTextAlignment(Qt::AlignCenter);
    category->setFlags(Qt::NoItemFlags);
    QStandardItem *date = new QStandardItem(ui->dateEdit->text());
    date->setTextAlignment(Qt::AlignCenter);
    QStandardItem *comment = new QStandardItem(ui->lineEditComment->text());
    comment->setTextAlignment(Qt::AlignCenter);
    row.append(cost);
    row.append(category);
    row.append(date);
    row.append(comment);

    _receiptModel->appendRow(row);

    // colorize every 2nd rows background
    const int rowIndex{_receiptModel->rowCount() - 1};
    if (QModelIndex index; rowIndex % 2 == 0)
    {
        const QColor color(173, 216, 230);
        for (int i = 0; i < _receiptModel->columnCount(); i++)
        {
            index = _receiptModel->index(rowIndex, i);
            _receiptModel->setData(index, color, Qt::BackgroundRole);
        }
    }
}

void ActivityReceipt::on_pushButtonRemoveItem_clicked()
{
    auto rows = ui->tableView->selectionModel()->selectedRows();
    // for removing multiple selections you must go from backwards, or the last one won't be removed!
    for(int i = rows.size() - 1; i > -1; i--)
    {
        _receiptModel->removeRow(rows[i].row());
    }
}


void ActivityReceipt::on_pushButtonRemoveAll_clicked()
{
    _receiptModel->clear();
}


void ActivityReceipt::on_pushButtonSave_clicked()
{
    QVector<QVector<QString>> data(_receiptModel->rowCount());
    int ind {0};
    QVector<QString> rowData;
    while (_receiptModel->rowCount() > 0)
    {
        rowData.clear();
        auto row{_receiptModel->takeRow(0)};
        rowData.emplaceBack(row.at(0)->text());
        rowData.emplaceBack(_categories.key(row.at(1)->text()));
        rowData.emplaceBack(row.at(2)->text());
        rowData.emplaceBack(row.at(3)->text());
        data[ind++] = rowData;
    }
    DataBaseHandler::getDbManager()->insertShoppingExpanse(std::move(data));
}

