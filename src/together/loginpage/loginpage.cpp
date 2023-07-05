#include "loginpage.h"
#include "ui_loginpage.h"
#include <QCryptographicHash>
#include <iostream>
LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    const QString PATH = "C:/Users/senec/Desktop/together/together/rcs/images/";
    ui->setupUi(this);
    ui->googleButton->setIcon(QIcon(PATH + "loginpage/google.svg"));
    ui->facebookButton->setIcon(QIcon(PATH + "loginpage/fb.svg"));
    ui->gitButton->setIcon(QIcon(PATH + "loginpage/git.svg"));

/*    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysql-mycocktaildb.alwaysdata.net"); //definition de l'hostname de la base de données
    db.setUserName("317095"); //definition du User
    db.setPassword("MyCocktail*"); //definition du MDP de la BDD
    db.setDatabaseName("paulz_together"); //definition du nom de la BDD*/
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("mycocktaildb_together");
    if(db.open())
    {
        std::cout << "Vous êtes maintenant connecté à " << std::endl;
        db.close();
    }
    else
    {
        std::cout << "La connexion a échouée, désolé" << std::endl;
    }

}

LoginPage::~LoginPage()
{
    delete ui;
}

QSqlDatabase LoginPage::getDb(){//getteur de l'objet db;
    return db;
}

void LoginPage::on_loginButton_clicked()
{
    if(db.isOpen()){
        QSqlQuery query;
        QString pseudo = ui->accountInput->text(),
                password = ui->passWordInput->text(),
                savedPassword;

        ui->loginButton->setEnabled(false);
        ui->loginButton->setText("Connexion...");

        query.prepare("SELECT  MotDePasse FROM Utilisateurs WHERE Pseudo = ?");
        query.addBindValue(pseudo);
        if (query.exec() && query.next()) {
            savedPassword = query.value(0).toString();

            if(savedPassword == password){
                MainChatPage = new ChatPage;
                MainChatPage->show();
                this->close();
                MainChatPage->setNom(pseudo);
                this->~LoginPage();
            }
            else{
                msg->warning(this, tr("formulaire incorrect"), tr("login ou mot de passe incorrect !"));
                ui->loginButton->setText("Connexion");
                ui->loginButton->setEnabled(true);
            }
        }
    }
    else
    {
         msg->warning(this, tr("erreur DB"), tr("erreur de connexion a la DB"));
    }
}

