#include "cpuwidget.h"
#include "sysinfo.h"

using namespace QtCharts; //all Qt Charts classes are defined in the QtCharts namespace

CpuWidget::CpuWidget(QWidget* parent) :
    SysInfoWidget(parent),
    mSeries(new QPieSeries(this)) //initialize mSeries in the constructor initializer list
{
    mSeries->setHoleSize(0.35); //carve the donut
    mSeries->append("CPU Load", 30.0);
    mSeries->append("CPU Free", 70.0);

    QChart* chart = chartView().chart(); //QChart class is retrieved
    chart->addSeries(mSeries); //chart takes the ownership of mSeries and will draw it according to the series type--in our case, a QPieSeries
    chart->setTitle("CPU average load");
}

void CpuWidget::updateSeries()
{
    double cpuLoadAverage = SysInfo::instance().cpuLoadAverage(); //get a reference to our SysInfo singleton, then retrieve the current average CPU load
    //mSeries object is a QPieCharts, which implies that we just want a snapshot of the current CPU average load
    mSeries->clear();
    mSeries->append("Load", cpuLoadAverage);
    mSeries->append("Free", 100.0 - cpuLoadAverage);
}
