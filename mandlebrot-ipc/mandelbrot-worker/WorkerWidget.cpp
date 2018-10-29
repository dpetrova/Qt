#include "WorkerWidget.h"

#include <QVBoxLayout>

WorkerWidget::WorkerWidget(QWidget *parent) :
    QWidget(parent),
    mStatus(this),
    mWorker(),
    mWorkerThread(this),
    mRefreshTimer()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(&mStatus); //mStatus variable is added to the WorkerWidget layout

    mWorker.moveToThread(&mWorkerThread); //mWorker thread affinity is moved to mWorkerThread

    //mRefreshTimer is configured to poll mWorker and update mStatus data
    connect(&mRefreshTimer, &QTimer::timeout, [this] {
        mStatus.setMaximum(mWorker.receivedJobsCounter());
        mStatus.setValue(mWorker.sentJobCounter());
    });

    mWorkerThread.start(); //mWorkerThread is started, triggering the mWorker process
    mRefreshTimer.start(100); //mRefreshTimer object is also started with an interval of 100 milliseconds between each timeout
}

WorkerWidget::~WorkerWidget()
{
    mWorkerThread.quit();
    mWorkerThread.wait(1000);
}
