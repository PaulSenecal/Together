#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent) :
    QObject(parent)
{
    //QThreadPool::globalInstance()->setMaxThreadCount(5);
}

void ClientSocket::Closed()
{
    socket->close();
}
void ClientSocket::Connect()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.216.1", 15000);

    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
        socket->write("\r hello server");
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();
        qDebug() << socket->readAll();
        connect(socket, &QTcpSocket::readyRead, this, &ClientSocket::onReadyRead);
    }
    else
    {
        qDebug() << "Not connected!";
    }

}
void ClientSocket::send(QByteArray text)
{
    socket->write(text);
}

void ClientSocket::onReadyRead()
{
    QByteArray datas=socket->readAll();
    socket->write(datas);
    emit dataReceived(datas);
}
void ClientSocket::disconnectFromHost()
{
    socket->abort();
}

