#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocol.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clientSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    // Setup Client
    setupClient();

    // Connect signals and slots
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(clientSocket, &QTcpSocket::readyRead, this, &MainWindow::onServerReadyRead);
    connect(clientSocket, &QTcpSocket::connected, this, &MainWindow::onClientConnected);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MainWindow::onClientDisconnected);
    connect(clientSocket, &QTcpSocket::errorOccurred, this, &MainWindow::onErrorOccurred); // Handle errors
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupClient()
{
    clientSocket->connectToHost("127.0.0.1", 1237);
    if (!clientSocket->waitForConnected(5000)) {  // Timeout after 5 seconds
        QMessageBox::critical(this, "Error", "Unable to connect to server");
        return;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (clientSocket->state() != QAbstractSocket::ConnectedState) {
        ui->textEdit->append("Error: Could not connect to the server.");
        return;
    }

    QString userId = ui->lineEdit->text();
    QString userName = ui->lineEdit_2->text();
    QString email = ui->lineEdit_3->text();

    sendDataToServer(userId, userName, email);
}

void MainWindow::sendDataToServer(const QString &userId, const QString &userName, const QString &email)
{
    QString message = QString("%1,%2,%3").arg(userId, userName, email);

    UserData data = {userId, userName, email};
    QByteArray serializedData = data.serialize(data);
    clientSocket->write(serializedData);

    // Báo cho người dùng khi dữ liệu được gửi đi
    ui->textEdit->append("Sending data to server: " + message);

    // Kết nối tín hiệu bytesWritten để kiểm tra khi gửi thành công
    connect(clientSocket, &QTcpSocket::bytesWritten, this, &MainWindow::onDataSent);
}

void MainWindow::onDataSent(qint64 bytes)
{
    Q_UNUSED(bytes);  // Không cần sử dụng giá trị `bytes` ở đây

    // Hiển thị thông báo khi dữ liệu được gửi đi thành công
    ui->textEdit->append("Data sent to server successfully");

    // Ngắt kết nối tín hiệu bytesWritten vì chỉ cần xử lý một lần
    disconnect(clientSocket, &QTcpSocket::bytesWritten, this, &MainWindow::onDataSent);
}

void MainWindow::onServerReadyRead()
{
    static QByteArray buffer;

    // Append incoming data to the buffer
    buffer.append(clientSocket->readAll());

    // Process complete messages
    while (buffer.contains('\n')) {  // Assuming each message ends with a newline
        int messageEnd = buffer.indexOf('\n');
        QByteArray message = buffer.left(messageEnd);
        buffer.remove(0, messageEnd + 1);  // Remove the processed message

        handleServerResponse(message);
    }
}

void MainWindow::onClientConnected()
{
    ui->textEdit->append("Connected to server");
}

void MainWindow::onClientDisconnected()
{
    ui->textEdit->append("Disconnected from server");
}

void MainWindow::handleServerResponse(const QByteArray &response)
{
    if (response.isEmpty()) {
        ui->textEdit->append("Received empty response");
        return;
    }

    // Check if the response is valid (simple check here, can be extended)
    if (response.contains("Malformed")) {
        ui->textEdit->append("Malformed data received from server");
    } else {
        ui->textEdit->append("Server Response: " + QString(response));
    }
}

void MainWindow::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    QString errorString;
    switch (socketError) {
    case QAbstractSocket::HostNotFoundError:
        errorString = "Host not found";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        errorString = "Connection refused";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        errorString = "Remote host closed the connection";
        break;
    case QAbstractSocket::SocketTimeoutError:
        errorString = "Connection timed out";
        break;
    default:
        errorString = clientSocket->errorString();
        break;
    }
    QMessageBox::critical(this, "Error", errorString);
}
