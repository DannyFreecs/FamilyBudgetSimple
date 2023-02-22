#ifndef ACTIVITYCHILD_H
#define ACTIVITYCHILD_H

#include <QMainWindow>

namespace Ui {
class ActivityChild;
}

class ActivityChild : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActivityChild(QWidget *parent = nullptr);
    ActivityChild(const QString& child, QWidget *parent = nullptr);
    ~ActivityChild();

private slots:
    void on_pushButtonSaveStudies_clicked();
    void on_pushButtonSaveOther_clicked();
    void checkStudyExpenseExistence() const;

private:
    void initStudyCostField() const;

private:
    Ui::ActivityChild *ui;
};

#endif // ACTIVITYCHILD_H
