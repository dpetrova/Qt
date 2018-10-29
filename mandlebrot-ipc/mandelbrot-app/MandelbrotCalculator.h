#ifndef MANDELBROTSERVER_H
#define MANDELBROTSERVER_H

#include <memory>
#include <vector>

#include <QTcpServer>
#include <QList>
#include <QThread>
#include <QMap>
#include <QElapsedTimer>

#include "WorkerClient.h"
#include "JobResult.h"
#include "JobRequest.h"

//has the responsibility to dispatch JobRequests to Workers and aggregate the result
class MandelbrotCalculator : public QTcpServer
{
    Q_OBJECT
public:
    MandelbrotCalculator(QObject* parent = 0);
    ~MandelbrotCalculator();

signals:
    void pictureLinesGenerated(QList<JobResult> jobResults);
    void abortAllJobs();

public slots:
    void generatePicture(QSize areaSize, QPointF moveOffset, double scaleFactor, int iterationMax);

private slots:
    void process(WorkerClient* workerClient, JobResult jobResult); //not only aggregates JobResults before sending them with the pictureLinesGenerated() signal, but also dispatches JobRequest to the passed WorkerClient to keep them busy.
    void removeWorkerClient(WorkerClient* workerClient); //removes and deletes the given WorkerClient from mWorkerClients

protected:
    void incomingConnection(qintptr socketDescriptor) override; //called each time a new client tries to connect to MandelbrotCalculator

private:
    std::unique_ptr<JobRequest> createJobRequest(int pixelPositionY); //helper function that creates a JobRequest that is added to mJobRequests
    void sendJobRequests(WorkerClient& client, int jobRequestCount = 1); //responsible for sending a list of JobRequests to the specified WorkerClient
    void clearJobs();

private:
    QPointF mMoveOffset;
    double mScaleFactor;
    QSize mAreaSize;
    int mIterationMax;
    int mReceivedJobResults;
    QList<JobResult> mJobResults;
    QMap<WorkerClient*, QThread*> mWorkerClients; //a QMap that stores the pair WorkerClient and QThread
    std::vector<std::unique_ptr<JobRequest>> mJobRequests; //list of JobRequests for the current picture
    QElapsedTimer mTimer;
};

#endif // MANDELBROTSERVER_H
