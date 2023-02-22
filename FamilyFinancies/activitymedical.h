#ifndef ACTIVITYMEDICAL_H
#define ACTIVITYMEDICAL_H

#include <QMainWindow>

namespace Ui {
class ActivityMedical;
}

class ActivityMedical : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActivityMedical(QWidget *parent = nullptr);
    ~ActivityMedical();

private slots:
    void on_pushButtonSave_clicked();

private:
    Ui::ActivityMedical *ui;
};

#endif // ACTIVITYMEDICAL_H
