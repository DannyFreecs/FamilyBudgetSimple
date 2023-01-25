#include "activityreceipt.h"
#include "ui_activityreceipt.h"
#include "databasehandler.h"

ActivityReceipt::ActivityReceipt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityReceipt)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());

    receiptModel = std::make_unique<QStandardItemModel>();
    receiptModel->setHorizontalHeaderItem(0, new QStandardItem("Összeg"));
    receiptModel->setHorizontalHeaderItem(1, new QStandardItem("Kategória"));
    receiptModel->setHorizontalHeaderItem(2, new QStandardItem("Dátum"));
    receiptModel->setHorizontalHeaderItem(3, new QStandardItem("Leírás"));

    ui->tableView->setModel(receiptModel.get());
    //ui->comboBoxCategories->addItems(DataBaseHandler::getDbManager()->getShoppingCategories());
    QStringList comboCategories {"Élelmiszer", "Drogéria", "Gyógyszertár", "Műszaki cikk", "Egyéb"};
    ui->comboBoxCategories->addItems(comboCategories);
}

ActivityReceipt::~ActivityReceipt()
{
    delete ui;
}

void ActivityReceipt::on_pushButtonAddItem_clicked()
{
    QList<QStandardItem*> row;
    QStandardItem *amount = new QStandardItem(ui->lineEditCostItem->text());
    amount->setTextAlignment(Qt::AlignCenter);
    QStandardItem *category = new QStandardItem(ui->comboBoxCategories->currentText());
    category->setTextAlignment(Qt::AlignCenter);
    category->setFlags(Qt::NoItemFlags);
    QStandardItem *date = new QStandardItem(ui->dateEdit->text());
    date->setTextAlignment(Qt::AlignCenter);
    QStandardItem *comment = new QStandardItem(ui->lineEditComment->text());
    comment->setTextAlignment(Qt::AlignCenter);
    row.append(amount);
    row.append(category);
    row.append(date);
    row.append(comment);
    receiptModel->appendRow(row);
}

void ActivityReceipt::on_pushButtonRemoveItem_clicked()
{
    auto rows = ui->tableView->selectionModel()->selectedRows();
    // for removing multiple selections you must go from backwards or the last one won't be removed!
    for(int i = rows.size() - 1; i > -1; i--)
    {
        receiptModel->removeRow(rows[i].row());
    }
}


void ActivityReceipt::on_pushButtonRemoveAll_clicked()
{
    receiptModel->clear();
}


void ActivityReceipt::on_pushButtonSave_clicked()
{
    QVector<QVector<QString>> data(receiptModel->rowCount());
    int ind {0};
    QVector<QString> rowData;
    while (receiptModel->rowCount() > 0)
    {
        rowData.clear();
        for (const auto &it : receiptModel->takeRow(0))
        {
            rowData.push_back(it->text());
        }
        data[ind++] = rowData;
    }
    DataBaseHandler::getDbManager()->insertShoppingExpanse(std::move(data));
}

