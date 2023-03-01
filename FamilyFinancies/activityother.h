#ifndef ACTIVITYOTHER_H
#define ACTIVITYOTHER_H

#include <QMainWindow>

namespace Ui {
class ActivityOther;
}

class ActivityOther : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActivityOther(QWidget *parent = nullptr);
    ~ActivityOther();

private slots:
    void on_pushButtonSave_clicked();

private:
    Ui::ActivityOther *ui;
};

#endif // ACTIVITYOTHER_H
