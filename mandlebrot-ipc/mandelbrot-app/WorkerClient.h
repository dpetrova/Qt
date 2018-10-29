#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QTcpSocket>
#include <QList>
#include <QDataStream>

#include "JobRequest.h"
#include "JobResult.h"
#include "Message.h"

//class responsible for maintaining the connection with a specific Worker
class WorkerClient : public QObject
{
    Q_OBJECT
public:
    WorkerClient(int socketDescriptor); //a WorkerClient cannot be initialized without a valid socket

    int cpuCoreCount() const; //a simple getter to let the owner of WorkerClient know how many cores the Worker has

signals:
    void unregistered(WorkerClient* workerClient); //signal sent by WorkerClient when it has received the WORKER_UNREGISTER message
    void jobCompleted(WorkerClient* workerClient, JobResult jobResult); //signal sent by WorkerClient when it has received the JOB_RESULT message
    void sendJobRequests(QList<JobRequest> requests); //emitted from the owner of WorkerClient to pass JobRequests in a queued connection to the proper slot

public slots:
    void start(); //slot is called when WorkerClient can start its process
    void abortJob(); //slot triggers the shipment of the ALL_JOBS_ABORT message to the Worker

private slots:
    void doSendJobRequests(QList<JobRequest> requests); //slot that triggers the shipment of the JobRequests to the Worker
    void readMessages(); //slot is called each time there is something to read in the socket

private:
    void handleWorkerRegistered(Message& message); //processes the WORKER_REGISTER message and initializes mCpuCoreCount
    void handleWorkerUnregistered(Message& message); //processes the WORKER_UNREGISTER message and emits the unregistered() signal
    void handleJobResult(Message& message); //processes the JOB_RESULT message and dispatches the content through the jobCompleted() signal

private:
    int mSocketDescriptor; //unique integer assigned by the system to interact with the socket
    int mCpuCoreCount; //CPU core count for the connected Worker
    QTcpSocket mSocket; //QTcpSocket used to interact with the Worker class
    QDataStream mSocketReader; //reads mSocket content
};

Q_DECLARE_METATYPE(WorkerClient*)

#endif // WORKERTHREAD_H
