#include "activityhouse.h"
#include "ui_activityhouse.h"
#include "yearmonthchooser.h"
#include "databasehandler.h"
#include <QVBoxLayout>

ActivityHouse::ActivityHouse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityHouse)
{
    ui->setupUi(this);

    setFixCosts();

    ui->dateEdit->setDate(QDate::currentDate());
    YearMonthChooser *mycalendar = new YearMonthChooser();
    ui->dateEdit->setCalendarWidget(mycalendar);

    ui->frameInsurance->setHidden(true);
    ui->frameOther->setHidden(true);
}

ActivityHouse::ActivityHouse(const QString& house, QWidget *parent) : ActivityHouse(parent)
{
    ui->labelAddress->setText(house);
}

ActivityHouse::~ActivityHouse()
{
    delete ui;
}

void ActivityHouse::setFixCosts()
{
    _fixCosts = DataBaseHandler::getDbManager()->getHouseFixCosts();

    ui->spinBoxGasBill->setValue(_fixCosts["Gáz"]);
    ui->spinBoxInternetBill->setValue(_fixCosts["Internet"]);
    ui->spinBoxCommonBill->setValue(_fixCosts["Közös költség"]);
    ui->spinBoxInsurance->setValue(_fixCosts["Biztosítás"]);
}

void ActivityHouse::on_toolButtonInsurance_clicked()
{
    ui->frameInsurance->setHidden(!ui->frameInsurance->isHidden());
    ui->toolButtonInsurance->setArrowType(ui->frameInsurance->isHidden() ? Qt::UpArrow : Qt::DownArrow);
}

void ActivityHouse::on_toolButtonOther_clicked()
{
    ui->frameOther->setHidden(!ui->frameOther->isHidden());
    ui->toolButtonOther->setArrowType(ui->frameOther->isHidden() ? Qt::UpArrow : Qt::DownArrow);
}

