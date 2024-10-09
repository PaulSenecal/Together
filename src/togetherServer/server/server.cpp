#include "server.h"

serverwin::serverwin() {
    // Construction de la fenêtre du serveur
    serverstatus = new QLabel;  // Étiquette qui affiche le port et l'adresse du serveur
    messagelbl = new QLabel;    // Étiquette qui affiche le message du client
    quitBtn = new QPushButton("Quitter le serveur");  // Bouton pour quitter le serveur

    // Gestion du clic sur le bouton quitter
    connect(quitBtn, SIGNAL(clicked()), qApp, SLOT(quit()));

    // Utilisation d'un Layout pour organiser les widgets dans la fenêtre
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(serverstatus);
    layout->addWidget(messagelbl);
    layout->addWidget(quitBtn);

    setLayout(layout);
    setWindowTitle("Serveur");

    // Gestion du serveur
    server = new QTcpServer(this);
    messagelbl->setText("Attente de client");

    if (!server->listen(QHostAddress::Any, 15000)) {  // Utilisation du port 15000 pour le serveur
        serverstatus->setText("Le serveur n'a pas pu être démarré :<br />" + server->errorString());
    } else {
        serverstatus->setText("Le serveur a été démarré avec l'adresse <strong>" +
                              getIPaddress() +
                              "</strong><br /> et le numéro de port <strong>" +
                              QString::number(server->serverPort()) + "</strong>.<br />");
        connect(server, SIGNAL(newConnection()), this, SLOT(connexion()));
    }

    tailleMessage = 0;  // La taille du message est nulle au démarrage
}

// Fonction pour obtenir l'adresse IP
QString serverwin::getIPaddress() {
    QStringList adresse;
    QString resultat;

    foreach(QHostAddress address, QNetworkInterface::allAddresses()) {
        if (address.isInSubnet(QHostAddress::parseSubnet("192.168.0.0/16"))) {
            resultat = address.toString();
            return resultat;
        }
    }

    return "Adresse Introuvable";
}

// Gestion de la connexion d'un client
void serverwin::connexion() {
    sendtoclient("<em> Un nouveau client est connecté </em>");

    QTcpSocket *nouveauClient = server->nextPendingConnection();
    client << nouveauClient;

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(getdata()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexion()));
}

// Récupération des messages des clients
void serverwin::getdata() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr) return;  // Émetteur du message non trouvé

    QDataStream in(socket);

    if (tailleMessage == 0) {
        if (socket->bytesAvailable() < static_cast<int>(sizeof(quint16))) return;  // Taille non reçue, on quitte
        in >> tailleMessage;  // On récupère la taille reçue
    }

    // Vérification que le message est complet
    if (socket->bytesAvailable() < tailleMessage) return;  // Message incomplet, on quitte

    QString message;
    in >> message;

    // Envoyer le message à tous les autres clients
    broadcastMessage(message, socket);

    messagelbl->setText(message);
    tailleMessage = 0;  // On remet la taille du message à 0
}

// Gestion de la déconnexion d'un client
void serverwin::deconnexion() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr) return;  // Client non trouvé

    client.removeOne(socket);
    socket->deleteLater();

    sendtoclient("<em> Un client s'est déconnecté </em>");
}

// Envoi d'un message à tous les clients connectés
void serverwin::sendtoclient(const QString &message) {
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    // Réservation de l'espace pour la taille du message
    out << static_cast<quint16>(0);
    out << message;

    // Revenir au début du paquet pour écrire la taille réelle
    out.device()->seek(0);
    out << static_cast<quint16>(paquet.size() - sizeof(quint16));

    // Envoyer à tous les clients connectés
    for (QTcpSocket *clientSocket : client) {
        clientSocket->write(paquet);
    }
}

// Diffusion d'un message à tous les clients sauf l'émetteur
void serverwin::broadcastMessage(const QString &message, QTcpSocket *senderSocket) {
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << static_cast<quint16>(0);  // Réservation de l'espace pour la taille du paquet
    out << message;  // Ajout du message au flux
    out.device()->seek(0);  // Retour au début du flux
    out << static_cast<quint16>(paquet.size() - sizeof(quint16));  // Taille du paquet

    // Diffuser à tous les clients, sauf à l'émetteur
    for (QTcpSocket *clientSocket : client) {
        if (clientSocket != senderSocket) {
            clientSocket->write(paquet);
            clientSocket->flush(); // Assure que les données sont immédiatement envoyées
        }
    }
}
/*
void serverwin::getdataFriend()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr) return;

    QDataStream in(socket);

    if (tailleMessage == 0) {
        if (socket->bytesAvailable() < static_cast<int>(sizeof(quint16))) return;
        in >> tailleMessage;
    }

    if (socket->bytesAvailable() < tailleMessage) return;

    QString command;
    in >> command;

    if (command == "VERIFY_FRIEND") {
        QString friendName;
        in >> friendName;
        bool exists = checkFriendInDB(friendName); // Vérifie dans la base de données

        // Réponse au client
        QByteArray response;
        QDataStream out(&response, QIODevice::WriteOnly);
        out << static_cast<quint16>(0) << QString(exists ? "FRIEND_EXISTS" : "FRIEND_NOT_FOUND");
        out.device()->seek(0);
        out << static_cast<quint16>(response.size() - sizeof(quint16));
        socket->write(response);
    }

    tailleMessage = 0;
}

bool serverwin::checkFriendInDB(const QString &friendName)
{
    // Code pour vérifier dans ta base de données si l'utilisateur existe.
    // Retourne true si trouvé, sinon false.
}
*/
