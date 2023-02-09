#include "activityhouse.h"
#include "ui_activityhouse.h"
#include "yearmonthchooser.h"
#include "databasehandler.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QMouseEvent>
#include <QSpinBox>

ActivityHouse::ActivityHouse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityHouse)
{
    ui->setupUi(this);

    hideWarnings();
    setupDateEdits();
    ui->frameInsurance->setHidden(true);
    ui->frameOther->setHidden(true);
}

ActivityHouse::ActivityHouse(const QString& house, QWidget *parent) : ActivityHouse(parent)
{
    ui->labelAddress->setText(house);
    _id = DataBaseHandler::getDbManager()->getHouseId(house);
    setFixCosts();
    checkHouseExpenseExistences();
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

void ActivityHouse::checkHouseExpenseExistences()
{
    if (DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Víz")
            && ui->spinBoxWaterBill->valueFromText(ui->spinBoxWaterBill->text()) > 0)
    {
        ui->labelWarnWater->setHidden(false);
    }
    if (DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Villany")
            && ui->spinBoxElectricityBill->valueFromText(ui->spinBoxElectricityBill->text()) > 0)
    {
        ui->labelWarnElectricity->setHidden(false);
    }
    if (DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Gáz")
            && ui->spinBoxGasBill->valueFromText(ui->spinBoxGasBill->text()) > 0)
    {
        ui->labelWarnGas->setHidden(false);
    }
    if (DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Közös költség")
            && ui->spinBoxCommonBill->valueFromText(ui->spinBoxCommonBill->text()) > 0)
    {
        ui->labelWarnCommon->setHidden(false);
    }
    if (DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Internet")
            && ui->spinBoxInternetBill->valueFromText(ui->spinBoxInternetBill->text()) > 0)
    {
        ui->labelWarnInternet->setHidden(false);
    }
    if (DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Biztosítás")
            && ui->spinBoxInsurance->valueFromText(ui->spinBoxInsurance->text()) > 0)
    {
        ui->labelWarnInsurance->setHidden(false);
    }
}

void ActivityHouse::setupDateEdits()
{
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCalendarWidget(new YearMonthChooser);
    auto le = ui->dateEdit->findChild<QLineEdit*>();
    le->setReadOnly(true);
    connect(le, &QLineEdit::selectionChanged, [=](){le->setSelection(0,0);});

    ui->dateEditOtherCost->setDate(QDate::currentDate());
    ui->dateEditInsurance->setDate(QDate::currentDate());
}

void ActivityHouse::saveHouseBills()
{
    QMap<QString, int> costs;
    int cost = ui->spinBoxWaterBill->valueFromText(ui->spinBoxWaterBill->text());
    if (cost > 0) costs.insert("Víz", cost);

    cost = ui->spinBoxGasBill->valueFromText(ui->spinBoxGasBill->text());
    if (cost > 0) costs.insert("Gáz", cost);

    cost = ui->spinBoxElectricityBill->valueFromText(ui->spinBoxElectricityBill->text());
    if (cost > 0) costs.insert("Villany", cost);

    cost = ui->spinBoxInternetBill->valueFromText(ui->spinBoxInternetBill->text());
    if (cost > 0) costs.insert("Internet", cost);

    cost = ui->spinBoxCommonBill->valueFromText(ui->spinBoxCommonBill->text());
    if (cost > 0) costs.insert("Közös költség", cost);

    DataBaseHandler::getDbManager()->insertHouseBills(ui->labelAddress->text(), ui->dateEdit->date(), std::move(costs));
}

void ActivityHouse::saveHouseInsurance()
{

}

void ActivityHouse::saveHouseOtherCost()
{

}

void ActivityHouse::hideWarnings()
{
    ui->labelWarnCommon->hide();
    ui->labelWarnElectricity->hide();
    ui->labelWarnGas->hide();
    ui->labelWarnInsurance->hide();
    ui->labelWarnInternet->hide();
    ui->labelWarnWater->hide();
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

void ActivityHouse::on_pushButtonSave_clicked()
{
    saveHouseBills();
}

