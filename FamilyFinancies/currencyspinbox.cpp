#include "currencyspinbox.h"

CurrencySpinBox::CurrencySpinBox(QWidget *parent) : QSpinBox(parent)
{
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setLocale(QLocale(QLocale::Hungarian, QLocale::Hungary));

}

QString CurrencySpinBox::textFromValue(int value) const
{
    return locale().toCurrencyString(costFromText(text()));
}

int CurrencySpinBox::valueFromText(const QString &text) const
{
    return costFromText(text);
}

int CurrencySpinBox::costFromText(const QString &text) const
{
    QString cost{};
    for (const auto c : text)
        if (c.isDigit())
            cost += c;

    return cost.toInt();
}
