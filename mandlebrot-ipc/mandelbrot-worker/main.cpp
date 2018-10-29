#include <QApplication>

#include "JobResult.h"

#include "WorkerWidget.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<JobResult>(); //registering JobResult with qRegisterMetaType because it is used in the signal/slot mechanism

    QApplication a(argc, argv);

    //instantiate a WorkerWidget layout and display it
    WorkerWidget workerWidget;
    workerWidget.show();

    return a.exec();
}
