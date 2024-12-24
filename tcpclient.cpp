#include "tcpclient.h"
#include <QTcpSocket>
#include <QDebug>

TcpClient::TcpClient(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
{
}

void TcpClient::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
}

void TcpClient::sendData(const QString &userId, const QString &userName, const QString &email)
{
    QString message = QString("%1,%2,%3").arg(userId, userName, email);
    socket->write(message.toUtf8());
}

void TcpClient::handleServerResponse(const QByteArray &data)
{
    qDebug() << "Server response: " << data;
}
