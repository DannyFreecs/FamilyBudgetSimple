#ifndef ACTIVITYRECEIPT_H
#define ACTIVITYRECEIPT_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <memory>

namespace Ui {
class ActivityReceipt;
}

class ActivityReceipt : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActivityReceipt(QWidget *parent = nullptr);
    ~ActivityReceipt();

private:
    Ui::ActivityReceipt *ui;
    std::unique_ptr<QStandardItemModel> receiptModel;
};

#endif // ACTIVITYRECEIPT_H
