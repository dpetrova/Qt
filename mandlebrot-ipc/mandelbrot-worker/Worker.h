#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#include "Message.h"
#include "JobResult.h"

class Job;
class JobRequest;

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(QObject* parent = 0);
    ~Worker();

    int receivedJobsCounter() const;
    int sentJobCounter() const;

signals:
    void abortAllJobs(); //a signal emitted when the Worker class receives the appropriate message

private slots:
    void readMessages(); //slot called each time there is something to read in mTcpSocket

private:
    void sendRegister();
    void sendJobResult(JobResult jobResult); //sends the JobResult object to mandelbrot-app
    void sendUnregister(); //sends the unregister message to mandelbrot-app
    void handleJobRequest(Message& message); //creates and dispatches a Job class
    void handleAllJobsAbort(Message& message); //cancels all the current jobs and clear the thread queue
    Job* createJob(const JobRequest& jobRequest); //a helper function to create and properly connect the signals of a new Job

private:
    QTcpSocket mSocket;
    QDataStream mSocketReader; //QDataStream class through which we will read mSocket content
    int mReceivedJobsCounter; //incremented each time a new JobRequest is received from mandelbrot-app
    int mSentJobsCounter; //incremented each time a new JobResult is sent to mandelbrot-app
};

#endif // WORKER_H
