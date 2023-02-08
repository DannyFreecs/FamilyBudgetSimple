#ifndef CURRENCYSPINBOX_H
#define CURRENCYSPINBOX_H

#include <QSpinBox>

class CurrencySpinBox : public QSpinBox
{
    Q_OBJECT
public:
    CurrencySpinBox(QWidget *parent = nullptr);
    QString textFromValue(int value) const override;
    int valueFromText(const QString &text) const override;

private:
    int costFromText(const QString &text) const;
};

#endif // CURRENCYSPINBOX_H
