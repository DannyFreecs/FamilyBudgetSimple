#ifndef ACTIVITYSHOPPINGITEM_H
#define ACTIVITYSHOPPINGITEM_H

#include <QMainWindow>

namespace Ui {
class ActivityShoppingItem;
}

class ActivityShoppingItem : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActivityShoppingItem(QWidget *parent = nullptr);
    ~ActivityShoppingItem();

private:
    Ui::ActivityShoppingItem *ui;
    QMap<QString, QString> _categories;
};

#endif // ACTIVITYSHOPPINGITEM_H
