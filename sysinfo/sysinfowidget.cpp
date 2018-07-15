#include "SysInfoWidget.h"

#include <QVBoxLayout>

using namespace QtCharts;

SysInfoWidget::SysInfoWidget(QWidget *parent,
                             int startDelayMs,
                             int updateSeriesDelayMs) :
    QWidget(parent),
    mChartView(this)
{
    //define the timer interval
    mRefreshTimer.setInterval(updateSeriesDelayMs);

    //slot to call whenever a timeout signal is triggered
    connect(&mRefreshTimer, &QTimer::timeout, this, &SysInfoWidget::updateSeries);

    //static function QTimer::singleShot() will start the real timer after a delay defined by startDelayMs
    QTimer::singleShot(startDelayMs, [this] { mRefreshTimer.start(); });

    mChartView.setRenderHint(QPainter::Antialiasing); //enables the antialiasing to smooth the chart drawing
    mChartView.chart()->legend()->setVisible(false); //hide the chart's legend to get a minimalist display

    //handles the layout to display
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(&mChartView);
    setLayout(layout);
}

QChartView& SysInfoWidget::chartView()
{
    return mChartView;
}
