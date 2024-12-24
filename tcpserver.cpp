#include "tcpserver.h"
#include <QDebug>
#include <QMessageBox>

TcpServer::TcpServer(QObject *parent) : QObject(parent), server(new QTcpServer(this))
{
    connect(server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

TcpServer::~TcpServer()
{
    server->close();
}

void TcpServer::startServer(quint16 port)
{
    if (!server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started on port" << port;
    }
}

void TcpServer::onNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &TcpServer::onClientDisconnected);
}

void TcpServer::onReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = clientSocket->readAll();
    qDebug() << "Received data:" << data;

    // Send a response back to client
    clientSocket->write("Data received\n");
}

void TcpServer::onClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    clientSocket->deleteLater();
    qDebug() << "Client disconnected";
}
