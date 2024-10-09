#include "chatpage.h"
#include "ui_chatpage.h"
#include <iostream>
ChatPage::ChatPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatPage),
    client(this)
{
    ui->setupUi(this);
    const QString PATH = "C:/Users/senec/Desktop/together/together/rcs/images/";

    setSoundh(9);
    setSounds(9);

    start =new QSoundEffect( this );
    std::cout<<"son"<<getSoundh();
    start->setSource ( QUrl("qrc:/Song/song/start.WAV"));
    start->setVolume ( getSounds() );



    QObject::connect ( ui->sendMessageQpushButton,SIGNAL(clicked()), start , SLOT(play()));

    ui->addFileQpushButton->setToolTip("Ajouter un fichier");
    ui->smileQpushButton->setToolTip("Ajouter un smiley");
    ui->sendMessageQpushButton->setToolTip("Envoyer un message");
    ui->vocalMessageQpushButton->setToolTip("Message vocal");
    ui->callQPushButton->setToolTip("Lancer un Appel");
    ui->videoQPushButton->setToolTip("Lancer un appel video");
    ui->verticalSeparatorQpushButton->setToolTip("Gerez vos parametre");
    ui->personQpushButton->setToolTip("Gere votre profil");
    ui->verticalSeparatorQpushButton->setToolTip("Gerez vos parametre");
    ui->addFriendQPushButton->setToolTip("Invité un ami");
    ui->chatQPushButton->setToolTip("chat");
    //ui->bellQpushButton->setIcon(QIcon(PATH + "chatpage/bell.svg"));
    ui->bellQpushButton->setToolTip("Activé/desactivé notification");
    ui->addFileQpushButton->setToolTip("Ajouter un ami");


    connect(&client,SIGNAL(dataReceived(QByteArray)),this,SLOT(afficherMessage(QByteArray)));
    client.Connect();
}

ChatPage::~ChatPage()
{
    delete ui;
}
void ChatPage::setNom(QString nom){
     this->setWindowTitle(nom);
}

void ChatPage::on_sendMessageQpushButton_clicked()
{
    qDebug("send message");
    QByteArray text = (windowTitle()+": "+ui->sendMessageTextEdit->toPlainText()).toUtf8();
    qDebug()<<text.size()<<"size";
    if(text.size()>0)
    {
        client.send(text);
        ui->sendMessageTextEdit->clear();
        ui->chatQtextEdit->setTextColor("yellow");
        ui->chatQtextEdit->append(text);
    }
}




void ChatPage::on_pushButton_clicked()//temporis
{
    qDebug("fermeture");
    client.Closed();
    this->close();
}
void ChatPage::afficherMessage(QByteArray data)
{
    qDebug()<<"display message";
    ui->chatQtextEdit->setTextColor("red");
    ui->chatQtextEdit->append(data);
}


void ChatPage::on_goToChatQpushButton_clicked(bool isSelected)
{
    ui->goToChatQpushButton->setStyleSheet("background: #262626;""border-radius: 6px;");
    ui->goToGroupQPushButton->setStyleSheet("");

}


void ChatPage::on_goToGroupQPushButton_clicked()
{
    ui->goToGroupQPushButton->setStyleSheet("background: #262626;""border-radius: 6px;");
    ui->goToChatQpushButton->setStyleSheet("");
}
int ChatPage::getSoundh()
{
    return this->soundh;
}
void ChatPage::setSoundh(int sound)
{
    this->soundh = sound;
}
int ChatPage::getSounds()
{
    return this->sounds;
}
void ChatPage::setSounds(int sound)
{
    this->sounds = sound;
}

void ChatPage::on_addFriendQPushButton_clicked()
{
    bool ok;
    QString friendName = QInputDialog::getText(this, tr("Ajouter un ami"),
                                               tr("Nom d'utilisateur:"), QLineEdit::Normal,
                                               "", &ok);
    if (ok && !friendName.isEmpty()) {

        if (checkFriendInDB(friendName)) {
            afficherAmi(friendName);
        } else {
            QMessageBox::warning(this, "Erreur", "Cet utilisateur n'existe pas dans la base de données.");
        }
    }
}
bool ChatPage::checkFriendInDB(const QString &friendName)
{
    if (!QSqlDatabase::database().isOpen()) {
        if (!connectToDatabase()) {
            QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données.");
            return false;
        }
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM admin WHERE login = :login");
    query.bindValue(":login", friendName);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de l'ami: " << query.lastError().text();
        return false;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        return true;
    }
    return false;
}

void ChatPage::afficherAmi(const QString &friendName)
{
    ui->friendsListWidget->addItem(friendName);
}


bool ChatPage::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Programmation/C++/Together/src/db/mydatabase.db");
    if (!db.open()) {
        qDebug() << "Erreur lors de la connexion à la base de données: " << db.lastError().text();
        return false;
    }
    return true;
}
//devra heriter de la fonction de connection a la db ou passer la verif au server , de meme pour la verif de connection
