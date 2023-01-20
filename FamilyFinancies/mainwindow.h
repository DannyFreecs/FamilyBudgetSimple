#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
//#include "databasehandler.h"
#include "submenuexpenses.h"

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
    Ui::MainWindow *ui;
    //std::shared_ptr<DataBaseHandler> _dbManager;
    std::unique_ptr<SubMenuExpenses> _subMenuExpenses;
};
#endif // MAINWINDOW_H
