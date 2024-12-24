#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void onServerReadyRead();
    void onClientConnected();
    void onClientDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onDataSent(qint64 bytes);

private:
    void setupClient();
    void sendDataToServer(const QString &userId, const QString &userName, const QString &email);
    void handleServerResponse(const QByteArray &response);

    Ui::MainWindow *ui;
    QTcpSocket *clientSocket;
};

#endif // MAINWINDOW_H
