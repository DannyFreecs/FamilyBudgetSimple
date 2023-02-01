#include "currencyspinbox.h"

CurrencySpinBox::CurrencySpinBox(QWidget *parent) : QSpinBox(parent)
{
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setLocale(QLocale(QLocale::Hungarian, QLocale::Hungary));

}

QString CurrencySpinBox::textFromValue(int value) const
{
    QString currText;
    for(int i = 0; i < text().length(); i++)
    {
        QChar c{text().at(i)};
        if (c.isDigit())
        {
            currText += c;
        }
    }

    return locale().toCurrencyString(currText.toInt());
}

int CurrencySpinBox::valueFromText(const QString &text) const
{
    return locale().toInt(text);
}
