#include "activityhouse.h"
#include "ui_activityhouse.h"
#include "yearmonthchooser.h"
#include "databasehandler.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QMouseEvent>
#include <QSpinBox>
#include <QMessageBox>

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

    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &ActivityHouse::checkHouseExpenseExistences);
    connect(ui->dateEditInsurance, &QDateEdit::dateChanged, this, &ActivityHouse::checkHouseExpenseExistences);

    connect(ui->spinBoxCommonBill, &QAbstractSpinBox::editingFinished, this, &ActivityHouse::checkHouseExpenseExistences);
    connect(ui->spinBoxElectricityBill, &QAbstractSpinBox::editingFinished, this, &ActivityHouse::checkHouseExpenseExistences);
    connect(ui->spinBoxGasBill, &QAbstractSpinBox::editingFinished, this, &ActivityHouse::checkHouseExpenseExistences);
    connect(ui->spinBoxInternetBill, &QAbstractSpinBox::editingFinished, this, &ActivityHouse::checkHouseExpenseExistences);
    connect(ui->spinBoxWaterBill, &QAbstractSpinBox::editingFinished, this, &ActivityHouse::checkHouseExpenseExistences);
    connect(ui->spinBoxInsurance, &QAbstractSpinBox::editingFinished, this, &ActivityHouse::checkHouseExpenseExistences);
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
    ui->labelWarnWater->setHidden(!(DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Víz")
                                  && ui->spinBoxWaterBill->valueFromText(ui->spinBoxWaterBill->text()) > 0));

    ui->labelWarnElectricity->setHidden(!(DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Villany")
                                            && ui->spinBoxElectricityBill->valueFromText(ui->spinBoxElectricityBill->text()) > 0));

    ui->labelWarnGas->setHidden(!(DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Gáz")
                                && ui->spinBoxGasBill->valueFromText(ui->spinBoxGasBill->text()) > 0));

    ui->labelWarnCommon->setHidden(!(DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Közös költség")
                                   && ui->spinBoxCommonBill->valueFromText(ui->spinBoxCommonBill->text()) > 0));

    ui->labelWarnInternet->setHidden(!(DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEdit->date(), "Rezsi", "Internet")
                                     && ui->spinBoxInternetBill->valueFromText(ui->spinBoxInternetBill->text()) > 0));

    ui->labelWarnInsurance->setHidden(!(DataBaseHandler::getDbManager()->checkHouseExpenseExistence(_id, ui->dateEditInsurance->date(), "Biztosítás")
                                        && ui->spinBoxInsurance->valueFromText(ui->spinBoxInsurance->text()) > 0));
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

void ActivityHouse::on_pushButtonSaveBills_clicked()
{
    QVector<std::pair<QString, int>> insert;
    QVector<std::pair<QString, int>> update;

    int cost = ui->spinBoxWaterBill->valueFromText(ui->spinBoxWaterBill->text());
    if (cost > 0) ui->labelWarnWater->isHidden() ? insert.emplaceBack("Víz", cost) : update.emplaceBack("Víz", cost);

    cost = ui->spinBoxGasBill->valueFromText(ui->spinBoxGasBill->text());
    if (cost > 0) ui->labelWarnGas->isHidden() ? insert.emplaceBack("Gáz", cost) : update.emplaceBack("Gáz", cost);

    cost = ui->spinBoxElectricityBill->valueFromText(ui->spinBoxElectricityBill->text());
    if (cost > 0) ui->labelWarnElectricity->isHidden() ? insert.emplaceBack("Villany", cost) : update.emplaceBack("Villany", cost);


    cost = ui->spinBoxInternetBill->valueFromText(ui->spinBoxInternetBill->text());
    if (cost > 0) ui->labelWarnInternet->isHidden() ? insert.emplaceBack("Internet", cost) : update.emplaceBack("Internet", cost);


    cost = ui->spinBoxCommonBill->valueFromText(ui->spinBoxCommonBill->text());
    if (cost > 0) ui->labelWarnCommon->isHidden() ? insert.emplaceBack("Közös költség", cost) : update.emplaceBack("Közös költség", cost);

    if (insert.size() > 0)
    {
        DataBaseHandler::getDbManager()->insertHouseBills(ui->labelAddress->text(), ui->dateEdit->date(), std::move(insert))
                ? QMessageBox::information(nullptr, "Mentés", "Sikeres mentés!")
                : QMessageBox::critical(nullptr, "Mentés", "A mentés során hiba történt!");
    }
    if (update.size() > 0)
    {
        QMessageBox msg;
        msg.setWindowTitle("Módosítás");
        msg.setText("Szeretné felülírni a korábbi rezsi költségeket?");
        auto yes = msg.addButton("Igen", QMessageBox::YesRole);
        msg.addButton("Nem", QMessageBox::NoRole);
        msg.exec();

        if (msg.clickedButton() == yes)
        {
            DataBaseHandler::getDbManager()->updateHouseBills(ui->labelAddress->text(), ui->dateEdit->date(), std::move(update))
                    ? QMessageBox::information(nullptr, "Módosítás", "Sikeres módosítás!")
                    : QMessageBox::critical(nullptr, "Módosítás", "A módosítás során hiba történt!");
        }
    }
}

void ActivityHouse::on_pushButtonSaveInsurance_clicked()
{
    int cost = ui->spinBoxInsurance->valueFromText(ui->spinBoxInsurance->text());
    if (cost > 0)
    {
        if (ui->labelWarnInsurance->isHidden())
        {
            DataBaseHandler::getDbManager()->insertHouseInsurance(ui->labelAddress->text(), ui->dateEditInsurance->date(), cost)
                    ? QMessageBox::information(nullptr, "Mentés", "Sikeres mentés!")
                    : QMessageBox::critical(nullptr, "Mentés", "A mentés során hiba történt!");
        }
        else
        {
            QMessageBox msg;
            msg.setWindowTitle("Módosítás");
            msg.setText("Szeretné felülírni a korábbi biztosítási díjat?");
            auto yes = msg.addButton("Igen", QMessageBox::YesRole);
            msg.addButton("Nem", QMessageBox::NoRole);
            msg.exec();

            if (msg.clickedButton() == yes)
            {
                DataBaseHandler::getDbManager()->updateHouseInsurance(ui->labelAddress->text(), ui->dateEditInsurance->date(), cost)
                        ? QMessageBox::information(nullptr, "Módosítás", "Sikeres módosítás!")
                        : QMessageBox::critical(nullptr, "Módosítás", "A módosítás során hiba történt!");
            }
        }
    }
}

void ActivityHouse::on_pushButtonSaveOther_clicked()
{
    if (ui->spinBoxOtherCost->valueFromText(ui->spinBoxOtherCost->text()) < 1)
    {
        QMessageBox::warning(nullptr, "Mentés", "Az összeg mezőben 0 Ft szerepel!");
        return;
    }

    QMap<QString, QString> expense;
    expense.insert("cost", QString::number(ui->spinBoxOtherCost->valueFromText(ui->spinBoxOtherCost->text())));
    expense.insert("date", ui->dateEditOtherCost->date().toString("yyyy-MM-dd"));
    expense.insert("comment", ui->lineEditComment->text());

    DataBaseHandler::getDbManager()->insertHouseOtherExpense(ui->labelAddress->text(), std::move(expense))
            ? QMessageBox::information(nullptr, "Mentés", "Sikeres mentés!")
            : QMessageBox::critical(nullptr, "Mentés", "A mentés során hiba történt!");

}

