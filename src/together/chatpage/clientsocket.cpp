#include "clientsocket.h"
//version avec Encodage QDataStream
#include "clientsocket.h"
#include <QDebug>

ClientSocket::ClientSocket(QObject *parent) :
    QObject(parent),
    socket(nullptr),
    tailleMessage(0) // Initialise la tailleMessage à 0
{
}

void ClientSocket::Closed()
{
    if (socket) {
        socket->close();
    }
}

void ClientSocket::Connect()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.1.31", 15000);

    if (socket->waitForConnected(3000)) {
        qDebug() << "Connected!";

        // Préparation du message à envoyer avec QDataStream
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);

        QString message = "Hello, server!";
        out << static_cast<quint16>(0);  // Place réservée pour la taille
        out << message;  // Écriture du message dans le flux
        out.device()->seek(0);  // Retour au début du flux pour écrire la taille
        out << static_cast<quint16>(data.size() - sizeof(quint16));  // Taille du paquet

        // Envoi du message au serveur
        socket->write(data);
        socket->flush(); // Assure que les données sont immédiatement envoyées
        socket->waitForBytesWritten(1000);

        connect(socket, &QTcpSocket::readyRead, this, &ClientSocket::onReadyRead);
    } else {
        qDebug() << "Not connected!";
    }
}

void ClientSocket::send(const QString &text)
{
    // Utilisation de QDataStream pour envoyer des données structurées
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << static_cast<quint16>(0);  // Réservation de l'espace pour la taille du paquet
    out << text;  // Ajout du texte au flux
    out.device()->seek(0);  // Retour au début du flux
    out << static_cast<quint16>(data.size() - sizeof(quint16));  // Taille du paquet

    socket->write(data);
    socket->flush(); // Assure que les données sont immédiatement envoyées
}

void ClientSocket::onReadyRead()
{
    QDataStream in(socket);

    if (tailleMessage == 0) {
        // Si la taille n'a pas encore été reçue, on vérifie si elle est disponible
        if (socket->bytesAvailable() < static_cast<int>(sizeof(quint16)))
            return;

        in >> tailleMessage;  // Lecture de la taille du message
    }

    // On attend que tout le message soit disponible
    if (socket->bytesAvailable() < tailleMessage)
        return;

    // Lecture du message
    QString message;
    in >> message;

    qDebug() << "Message reçu du serveur:" << message;

    // Réinitialisation pour la prochaine réception
    tailleMessage = 0;

    emit dataReceived(message.toUtf8());
}

void ClientSocket::disconnectFromHost()
{
    if (socket) {
        socket->abort();
    }
}


/* version avec encodage brut
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
    socket->connectToHost("10.3.206.243", 15000);

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
*/
