#ifndef ACTIVITYHOUSE_H
#define ACTIVITYHOUSE_H

#include <QMainWindow>

namespace Ui {
class ActivityHouse;
}

class ActivityHouse : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActivityHouse(QWidget *parent = nullptr);
    ActivityHouse(const QString& house, QWidget *parent = nullptr);
    ~ActivityHouse();

private:
    void setFixCosts();
    void setupDateEdits();

private slots:
    void on_toolButtonInsurance_clicked();
    void on_toolButtonOther_clicked();

private:
    Ui::ActivityHouse *ui;
    QMap<QString, int> _fixCosts;
};

#endif // ACTIVITYHOUSE_H
