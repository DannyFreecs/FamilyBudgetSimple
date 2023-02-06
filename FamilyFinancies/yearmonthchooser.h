#ifndef YEARMONTHCHOOSER_H
#define YEARMONTHCHOOSER_H

#include <QObject>
#include <QCalendarWidget>
#include <QTableView>
#include <QToolButton>

class YearMonthChooser : public QCalendarWidget
{
public:
    YearMonthChooser(QWidget *parent = nullptr);
    void paintCell(QPainter *painter, const QRect& rect, QDate date) const override;

public slots:
    void onCellPressed(const QModelIndex &index);
    void onPrevYearPressed();
    void onNextYearPressed();

private:
    QTableView *_tableView;
    QToolButton *_monthButton;
    QToolButton *_yearButton;
    QToolButton *_prevButton;
    QToolButton *_nextButton;
};

#endif // YEARMONTHCHOOSER_H
