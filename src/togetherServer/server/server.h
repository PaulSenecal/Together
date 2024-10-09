#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets> //pour une version QT5 remplacer QtGui par QtWidgets

#include <QtNetwork>



class serverwin : public QWidget        //description de l'objet serverwin

{

    Q_OBJECT

public:

    serverwin();
    void getdataFriend();
    void checkFriendInDB(const QString &friendName);


private slots:  //les slots de gestion des évènements

    void connexion();
    void getdata();
    void deconnexion();




private:

    QLabel *serverstatus;//affiche l'état du serveur
    QLabel *messagelbl; //affiche le message du client
    QPushButton *quitBtn;
    QTcpServer *server;
    QList<QTcpSocket *> client;
    quint16 tailleMessage;
    QString getIPaddress();
    void broadcastMessage(const QString &message, QTcpSocket *senderSocket);
    void sendtoclient(const QString &message);

};
#endif // SERVER_H
