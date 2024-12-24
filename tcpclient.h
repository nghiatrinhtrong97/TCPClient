#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void sendData(const QString &userId, const QString &userName, const QString &email);
    void handleServerResponse(const QByteArray &data);

private:
    QTcpSocket *socket;
};

#endif // TCPCLIENT_H
