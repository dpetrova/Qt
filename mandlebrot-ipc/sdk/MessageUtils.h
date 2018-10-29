#ifndef MESSAGEUTILS_H
#define MESSAGEUTILS_H

#include <memory>
#include <vector>
#include <QByteArray>
#include <QTcpSocket>
#include <QDataStream>

#include "Message.h"

namespace MessageUtils {

//To explicitly indicate ownership and avoid any memory leaks, we return a vector<unique_ptr<Message>>. This vector has to be a unique_ptr pointer to be able to
//allocate it on the heap and avoid any copy during the return of the function
inline std::unique_ptr<std::vector<std::unique_ptr<Message>>> readMessages(QDataStream& stream) //
{
    auto messages = std::make_unique<std::vector<std::unique_ptr<Message>>>(); //declaring the vector
    bool commitTransaction = true;
    while (commitTransaction && //atomic read in the stream that has been performed
           stream.device()->bytesAvailable() > 0) { //there is still data to read in the stream
        stream.startTransaction(); //start transaction
        auto message = std::make_unique<Message>();
        stream >> *message; //perform an atomic read of a *message signal
        commitTransaction = stream.commitTransaction(); //result of transaction
        if (commitTransaction) { //If it succeeded, the new message is added to the messages vector
            messages->push_back(std::move(message));
        }
    }
    return messages;
}

inline void sendMessage(QTcpSocket& socket, //QTcpSocket class in which the message will be sent
                        Message::Type messageType, //type of the message to be sent
                        QByteArray& data, //serialized data to be included in the message
                        bool forceFlush = false) //flag to force the socket to flush upon the message shipment
{
    Message message(messageType, data);

    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << message;
    socket.write(byteArray);
    if (forceFlush) {
        socket.flush();
    }
}

inline void sendMessage(QTcpSocket& socket,
                        Message::Type messageType,
                        bool forceFlush = false) {
    QByteArray data;
    sendMessage(socket, messageType, data, forceFlush);
}

}

#endif // MESSAGEUTILS_H
