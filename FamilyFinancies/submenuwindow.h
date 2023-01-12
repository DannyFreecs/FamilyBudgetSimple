#ifndef SUBMENUWINDOW_H
#define SUBMENUWINDOW_H

#include <QMainWindow>

namespace Ui {
class SubMenuWindow;
}

class SubMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubMenuWindow(QWidget *parent = nullptr);
    ~SubMenuWindow();

private:
    Ui::SubMenuWindow *ui;
};

#endif // SUBMENUWINDOW_H
