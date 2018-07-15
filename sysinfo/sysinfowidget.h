#ifndef SYSINFOWIDGET_H
#define SYSINFOWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QtCharts/QChartView>

class SysInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SysInfoWidget(QWidget *parent = 0,
                               int startDelayMs = 500,
                               int updateSeriesDelayMs = 500);

protected:
    QtCharts::QChartView& chartView();

protected slots:
    virtual void updateSeries() = 0; //pure virtual slot

private:
    QTimer mRefreshTimer; //QTimer will call the slot function updateSeries() regularly
    QtCharts::QChartView mChartView; //QChartView is the generic widget that can display many types of chart
};

#endif // SYSINFOWIDGET_H
