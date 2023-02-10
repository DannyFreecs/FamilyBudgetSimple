#ifndef YEARMONTHCHOOSER_H
#define YEARMONTHCHOOSER_H

#include <QObject>
#include <QCalendarWidget>
#include <QTableView>
#include <QToolButton>

class YearMonthChooser : public QCalendarWidget
{
    Q_OBJECT
public:
    YearMonthChooser(QWidget *parent = nullptr);
    void paintCell(QPainter *painter, const QRect& rect, QDate date) const override;

public slots:
    void onCellPressed(const QModelIndex &index);
    void onPrevYearPressed();
    void onNextYearPressed();

private:    
    QToolButton *_yearButton;    
};

#endif // YEARMONTHCHOOSER_H
