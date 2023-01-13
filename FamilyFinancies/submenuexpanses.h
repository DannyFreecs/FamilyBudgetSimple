#ifndef SUBMENUEXPANSES_H
#define SUBMENUEXPANSES_H

#include <QMainWindow>

namespace Ui {
class SubMenuExpanses;
}

class SubMenuExpanses : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubMenuExpanses(QWidget *parent = nullptr);
    ~SubMenuExpanses();

private:
    Ui::SubMenuExpanses *ui;
};

#endif // SUBMENUEXPANSES_H
