#include "yearmonthchooser.h"

#include <QStandardItemModel>
#include <QPainter>
#include <QToolButton>

YearMonthChooser::YearMonthChooser(QWidget *parent) : QCalendarWidget(parent)
{
    setGridVisible(true);
    setHorizontalHeaderFormat(QCalendarWidget::NoHorizontalHeader);
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    setLocale(QLocale(QLocale::Hungarian, QLocale::Hungary));
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    QStandardItemModel *model = new QStandardItemModel(4, 3);
    _tableView = findChild<QTableView*>();
    _tableView->setModel(model);
    _tableView->setShowGrid(true);
    _tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    _monthButton = findChild<QToolButton*>("qt_calendar_monthbutton");
    _monthButton->setEnabled(false);
    _monthButton->setHidden(true);
    _yearButton = findChild<QToolButton*>("qt_calendar_yearbutton");
    _prevButton = findChild<QToolButton*>("qt_calendar_prevmonth");
    _nextButton = findChild<QToolButton*>("qt_calendar_nextmonth");

    connect(_tableView, &QAbstractItemView::pressed, this, &YearMonthChooser::onCellPressed);
    connect(_prevButton, &QAbstractButton::pressed, this, &YearMonthChooser::onPrevYearPressed);
    connect(_nextButton, &QAbstractButton::pressed, this, &YearMonthChooser::onNextYearPressed);
}

void YearMonthChooser::paintCell(QPainter *painter, const QRect &rect, QDate date) const
{
    int row = rect.y() / rect.height();
    int col = rect.x() / rect.width();

    date = QDate(date.year(), 3 * row + col + 1, 1);
    QFont bold("Segoe UI", 9);
    bold.setBold(true);
    painter->setFont(bold);
    painter->drawText(rect, locale().toString(date, "MMMM"), QTextOption(Qt::AlignCenter));
}

void YearMonthChooser::onCellPressed(const QModelIndex &index)
{
    QDate date = QDate(_yearButton->text().toInt(), 3 * index.row() + index.column() + 1, QDate::currentDate().day());
    emit clicked(date);
}

void YearMonthChooser::onPrevYearPressed()
{
    setSelectedDate(QDate(yearShown() - 1, selectedDate().month(), 1));
}

void YearMonthChooser::onNextYearPressed()
{
    setSelectedDate(QDate(yearShown() + 1, selectedDate().month(), 1));
}

