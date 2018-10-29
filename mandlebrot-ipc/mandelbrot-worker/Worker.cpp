#include "Worker.h"

#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <QHostAddress>

#include "Job.h"
#include "JobRequest.h"
#include "MessageUtils.h"

Worker::Worker(QObject* parent) :
    QObject(parent),
    mSocket(this),
    mSocketReader(&mSocket),
    mReceivedJobsCounter(0),
    mSentJobsCounter(0)
{
    connect(&mSocket, &QTcpSocket::connected, [this] { //When the socket is connected, it will send its register message
        qDebug() << "Connected";
        sendRegister();
    });
    connect(&mSocket, &QTcpSocket::disconnected, [] { //When the socket is disconnected, it simply prints a message in the console
        qDebug() << "Disconnected";
    });
    connect(&mSocket, &QTcpSocket::readyRead,
            this, &Worker::readMessages);

    mSocket.connectToHost(QHostAddress::LocalHost, 5000); //Finally, mSocket tries to connect on the localhost on the port 5000
}

Worker::~Worker()
{
    sendUnregister();
}

void Worker::sendRegister()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << QThread::idealThreadCount();
    MessageUtils::sendMessage(mSocket,
                              Message::Type::WORKER_REGISTER,
                              data);
}

void Worker::sendJobResult(JobResult jobResult)
{
    mSentJobsCounter++; //first increment the mSentJobsCounter
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << jobResult; //A QByteArray class is filled with the idealThreadCount function of the worker's machine (serialize the JobResult to a QByteArray data)
    MessageUtils::sendMessage(mSocket, Message::Type::JOB_RESULT, data); //serialize the message and send it through our mSocket
}

void Worker::sendUnregister()
{
    //just calls sendMessage without any data to serialize
    //passes the forceFlush flag to true to make sure that the socket is flushed and that mandelbrot-app application will receive the message as fast as possible
    MessageUtils::sendMessage(mSocket,
                              Message::Type::WORKER_UNREGISTER,
                              true);
}

void Worker::readMessages()
{
    auto messages = MessageUtils::readMessages(mSocketReader); //parse messages
    for(auto& message : *messages) {
        switch (message->type) {
            case Message::Type::JOB_REQUEST:
                handleJobRequest(*message);
                break;
            case Message::Type::ALL_JOBS_ABORT:
                handleAllJobsAbort(*message);
                break;
            default:
                break;
        }
    }
}

void Worker::handleJobRequest(Message& message)
{
     QDataStream in(&message.data, QIODevice::ReadOnly); //create a QDataStream in a variable that will read from message.data
     QList<JobRequest> requests;
     in >> requests; //parse the requests QList. Because QList already overrides the >> operator, it works in cascade and calls our JobRequest >> operator overload

     mReceivedJobsCounter += requests.size(); //increment mReceivedJobsCounter
     for(const JobRequest& jobRequest : requests) {
         QThreadPool::globalInstance()->start(createJob(jobRequest)); //start processing these JobRequests -> for each one, we create a Job class and dispatch it to the global QThreadPool class
     }
}

void Worker::handleAllJobsAbort(Message& /*message*/)
{
    emit abortAllJobs(); //abortAllJobs() signal is emitted first to tell all the running jobs to cancel their process
    QThreadPool::globalInstance()->clear(); //QThreadPool class is cleared
    //reset counters
    mReceivedJobsCounter = 0;
    mSentJobsCounter = 0;
}

Job* Worker::createJob(const JobRequest& jobRequest)
{
    Job* job = new Job(jobRequest); //new Job class is created

    //its signals are properly connected
    connect(this, &Worker::abortAllJobs,
            job, &Job::abort);
    connect(job, &Job::jobCompleted,
            this, &Worker::sendJobResult);
    return job;
}

int Worker::sentJobCounter() const
{
    return mSentJobsCounter;
}

int Worker::receivedJobsCounter() const
{
    return mReceivedJobsCounter;
}
