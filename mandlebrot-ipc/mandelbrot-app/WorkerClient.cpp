#include "WorkerClient.h"

#include "MessageUtils.h"

WorkerClient::WorkerClient(int socketDescriptor) :
    QObject(),
    mSocketDescriptor(socketDescriptor),
    mSocket(this),
    mSocketReader(&mSocket)
{
    connect(this, &WorkerClient::sendJobRequests, this, &WorkerClient::doSendJobRequests);
}

void WorkerClient::start()
{
    connect(&mSocket, &QTcpSocket::readyRead, this, &WorkerClient::readMessages);
    mSocket.setSocketDescriptor(mSocketDescriptor);
}

void WorkerClient::abortJob()
{
    MessageUtils::sendMessage(mSocket, Message::Type::ALL_JOBS_ABORT, true); //sends the ALL_JOBS_ABORT message with the forceFlush flag set to true
}

void WorkerClient::doSendJobRequests(QList<JobRequest> requests)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly); //serializes the requests to stream before sending them
    stream << requests;

    MessageUtils::sendMessage(mSocket, Message::Type::JOB_REQUEST, data);
}

void WorkerClient::readMessages()
{
    auto messages = MessageUtils::readMessages(mSocketReader); //messages are deserialized
    for(auto& message : *messages) {
        switch (message->type) {
            case Message::Type::WORKER_REGISTER:
                handleWorkerRegistered(*message);
                break;
            case Message::Type::WORKER_UNREGISTER:
                handleWorkerUnregistered(*message);
                break;
            case Message::Type::JOB_RESULT:
                handleJobResult(*message);
                break;
            default:
                break;
        }
    }
}

void WorkerClient::handleWorkerRegistered(Message& message)
{
    QDataStream in(&message.data, QIODevice::ReadOnly); //serialized an int in message.data
    in >> mCpuCoreCount; //initialize mCpuCoreCount
}

void WorkerClient::handleWorkerUnregistered(Message& /*message*/)
{
    emit unregistered(this);
}

void WorkerClient::handleJobResult(Message& message)
{
    QDataStream in(&message.data, QIODevice::ReadOnly); //deserializes the jobResult component from message.data
    JobResult jobResult;
    in >> jobResult;
    emit jobCompleted(this, jobResult);
}

int WorkerClient::cpuCoreCount() const
{
    return mCpuCoreCount;
}
