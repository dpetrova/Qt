#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QDataStream>

struct Message {

    enum class Type {
        WORKER_REGISTER, //message sent by the worker when it first connects to the application
        WORKER_UNREGISTER, //message sent by the worker when it is disconnected
        ALL_JOBS_ABORT, //message sent by the application each time a picture generation is canceled
        JOB_REQUEST, //message sent by the application to calculate a specific line of the desired picture
        JOB_RESULT, //message sent by the worker with the calculated result
    };

    Message(const Type type = Type::WORKER_REGISTER, const QByteArray& data = QByteArray()) :
        type(type),
        data(data)
    {
    }

    ~Message() {}

    Type type; //message type
    QByteArray data; //contains the piece of information to be transmitted
};

inline QDataStream &operator<<(QDataStream &out, const Message &message)
{
    out <<  static_cast<qint8>(message.type)
        << message.data;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, Message &message)
{
    qint8 type;
    in >> type;
    in >> message.data;

    message.type = static_cast<Message::Type>(type);
    return in;
}

#endif // MESSAGE_H
