#include "loginpage.h"
#include "ui_loginpage.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);

    // Initialisation de la connexion à la base de données
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Programmation/C++/Together/src/db/mydatabase.db");

    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        QMessageBox::warning(this, tr("Database Error"), tr("Failed to connect to the database."));
    }
}

LoginPage::~LoginPage()
{
    delete ui;
}

QSqlDatabase LoginPage::connectionDataBase()
{
    return db;
}

void LoginPage::on_loginButton_clicked()
{
    if (db.isOpen()) {
        QSqlQuery query;
        QString pseudo = ui->accountInput->text();
        QString password = ui->passWordInput->text();
        QString savedPassword;

        qDebug() << "Attempting login with username:" << pseudo;

        ui->loginButton->setEnabled(false);
        ui->loginButton->setText("Connecting...");

        query.prepare("SELECT password FROM admin WHERE login = ?");
        query.addBindValue(pseudo);

        if (query.exec() && query.next()) {
            savedPassword = query.value(0).toString();

            if (savedPassword == password) {
                MainChatPage = new ChatPage;
                MainChatPage->show();
                this->close();
                MainChatPage->setNom(pseudo);
            } else {
                QMessageBox::warning(this, tr("Incorrect Form"), tr("Incorrect username or password!"));
                ui->loginButton->setText("Login");
                ui->loginButton->setEnabled(true);
            }
        } else {
            qDebug() << "Query failed:" << query.lastError().text();
            QMessageBox::warning(this, tr("Database Error"), tr("Failed to execute query."));
            ui->loginButton->setText("Login");
            ui->loginButton->setEnabled(true);
        }
    } else {
        QMessageBox::warning(this, tr("Database Error"), tr("Failed to connect to the database."));
    }
}
