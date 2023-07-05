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
    start->setSource ( QUrl :: fromLocalFile ( PATH + "song/start.wav" ));
    start->setVolume ( getSounds() );



    QObject::connect ( ui->sendMessageQpushButton,SIGNAL(clicked()), start , SLOT(play()));

    ui->addFileQpushButton->setIcon(QIcon(PATH + "chatpage/addFile.svg"));
    ui->addFileQpushButton->setToolTip("Ajouter un fichier");

    ui->smileQpushButton->setIcon(QIcon(PATH + "chatpage/smile.svg"));
    ui->smileQpushButton->setToolTip("Ajouter un smiley");

    ui->sendMessageQpushButton->setIcon(QIcon(PATH + "chatpage/send.svg"));
    ui->sendMessageQpushButton->setToolTip("Envoyer un message");

    ui->verticalSeparatorQpushButton->setIcon(QIcon(PATH + "chatpage/verticalSeparator.svg"));

    ui->vocalMessageQpushButton->setIcon(QIcon(PATH + "chatpage/vocalMessage.svg"));
    ui->vocalMessageQpushButton->setToolTip("Message vocal");

    ui->callQPushButton->setIcon(QIcon(PATH + "chatpage/phone.svg"));
    ui->callQPushButton->setToolTip("Lancer un Appel");


    ui->videoQPushButton->setIcon(QIcon(PATH + "chatpage/camera.svg"));
    ui->videoQPushButton->setToolTip("Lancer un appel video");

    ui->settingDoteQPushButton->setIcon(QIcon(PATH + "chatpage/settingDote.svg"));
    ui->verticalSeparatorQpushButton->setToolTip("Gerez vos parametre");

    ui->personQpushButton->setIcon(QIcon(PATH + "chatpage/my.svg"));
    ui->personQpushButton->setToolTip("Gere votre profil");

    ui->settingQPushButton->setIcon(QIcon(PATH + "chatpage/settingWile.svg"));
    ui->verticalSeparatorQpushButton->setToolTip("Gerez vos parametre");

    ui->addFriendQPushButton->setIcon(QIcon(PATH + "chatpage/addFriend.svg"));
    ui->addFriendQPushButton->setToolTip("Invité un ami");

    ui->chatQPushButton->setIcon(QIcon(PATH + "chatpage/chatBull.svg"));
    ui->chatQPushButton->setToolTip("chat");

    ui->bellQpushButton->setIcon(QIcon(PATH + "chatpage/bell.svg"));
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
    nom = "Bienvenu : "+nom;
    this->setWindowTitle("session de : "+nom);
}

void ChatPage::on_sendMessageQpushButton_clicked()
{
    qDebug("send message");
    QByteArray text = (ui->sendMessageTextEdit->toPlainText()).toUtf8();
    qDebug()<<text.size()<<"size";
    if(text.size()>0)
    {
        client.send(text);
        ui->sendMessageTextEdit->clear();
        ui->chatQtextEdit->setTextColor("yellow");
        ui->chatQtextEdit->append("me : " + text);
    }
}


void ChatPage::on_pushButton_clicked()//temporis
{
    qDebug("fermeture");
    client.Closed();
}
void ChatPage::afficherMessage(QByteArray data)
{
    qDebug()<<"display message";
    ui->chatQtextEdit->setTextColor("red");
    ui->chatQtextEdit->append("server: " + data);
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
