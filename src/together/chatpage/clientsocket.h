#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);
    void Connect();
    void Closed();
    void send(const QString &text);
    void disconnectFromHost();

signals:
    void dataReceived(QByteArray);
public slots:
    void onReadyRead();


private:
    QTcpSocket *socket;
    quint16 tailleMessage = 0;

};
#endif // CLIENTSOCKET_H
