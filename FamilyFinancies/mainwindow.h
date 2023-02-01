#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//ATTRIBUTIONS: <a href="https://www.freepik.com/free-vector/home-budget-icons-set_4017023.htm">Image by macrovector</a> on Freepik
// <a href="https://www.flaticon.com/free-icons/budget" title="budget icons">Budget icons created by Freepik - Flaticon</a>
// <a href="https://www.flaticon.com/free-icons/budget" title="budget icons">Budget icons created by Flat Icons - Flaticon</a>

#include <QMainWindow>
#include <memory>
#include "submenuexpenses.h"
#include "activityreceipt.h"
#include "activityshoppingitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void releaseActivites();
    void releasesubMenus();
    void setMenuButtonsToDefaultStyle();
    void setMenuButtonsSelectedStyle(QPushButton *button);

private slots:
    void on_createActivityReceipt();
    void on_createActivityShoppingItem();
    void on_menuButtonExpenses_clicked();
    void on_actionAddBlock_triggered();
    void on_actionAddItem_triggered();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<SubMenuExpenses> _subMenuExpenses;
    std::unique_ptr<ActivityReceipt> _activityReceipt;
    std::unique_ptr<ActivityShoppingItem> _activityShoppingItem;
};
#endif // MAINWINDOW_H
