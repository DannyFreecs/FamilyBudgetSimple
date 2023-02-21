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

private:
    Ui::ActivityChild *ui;
};

#endif // ACTIVITYCHILD_H
