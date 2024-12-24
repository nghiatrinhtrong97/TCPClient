#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QString>
#include <QDataStream>

struct UserData {
    QString userID;
    QString userName;
    QString email;

    // Serialize UserData into a byte array
    static QByteArray serialize(const UserData &data) {
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        stream << data.userID << data.userName << data.email;
        return byteArray;
    }

    // Deserialize byte array into UserData
    static UserData deserialize(const QByteArray &byteArray) {
        UserData data;
        QDataStream stream(byteArray);
        stream >> data.userID >> data.userName >> data.email;
        return data;
    }
};

#endif // PROTOCOL_H
