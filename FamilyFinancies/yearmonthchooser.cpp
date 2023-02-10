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
    auto tableView = findChild<QTableView*>();
    tableView->setModel(model);
    tableView->setShowGrid(true);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto monthButton = findChild<QToolButton*>("qt_calendar_monthbutton");
    monthButton->setEnabled(false);
    monthButton->setHidden(true);

    _yearButton = findChild<QToolButton*>("qt_calendar_yearbutton");

    connect(tableView, &QAbstractItemView::pressed, this, &YearMonthChooser::onCellPressed);
    connect(findChild<QToolButton*>("qt_calendar_prevmonth"), &QAbstractButton::pressed, this, &YearMonthChooser::onPrevYearPressed);
    connect(findChild<QToolButton*>("qt_calendar_nextmonth"), &QAbstractButton::pressed, this, &YearMonthChooser::onNextYearPressed);
}

void YearMonthChooser::paintCell(QPainter *painter, const QRect &rect, QDate date) const
{
    int row = rect.y() / rect.height();
    int col = rect.x() / rect.width();

    date = QDate(date.year(), 3 * row + col + 1, 1);
    QFont font("Segoe UI", 9);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(rect, locale().toString(date, "MMMM"), QTextOption(Qt::AlignCenter));
}

void YearMonthChooser::onCellPressed(const QModelIndex &index)
{
    QDate date = QDate(_yearButton->text().toInt(), 3 * index.row() + index.column() + 1, 1);
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

