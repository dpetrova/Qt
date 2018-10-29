#ifndef WORKERWIDGET_H
#define WORKERWIDGET_H

#include <QWidget>
#include <QThread>
#include <QProgressBar>
#include <QTimer>

#include "Worker.h"

class WorkerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WorkerWidget(QWidget *parent = 0);
    ~WorkerWidget();

private:
    QProgressBar mStatus; //QProgressBar that will display the percentage of processed JobRequests
    Worker mWorker; //Worker instance owned and started by WorkerWidget
    QThread mWorkerThread; //QThread class in which mWorker will be executed
    QTimer mRefreshTimer; //QTimer class that will periodically poll mWorker to know the process advancement
};

#endif // WORKERWIDGET_H
