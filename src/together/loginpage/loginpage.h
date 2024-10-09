#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "chatpage/chatpage.h"

class ChatPage;
QT_BEGIN_NAMESPACE
namespace Ui { class LoginPage; }
QT_END_NAMESPACE

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    LoginPage(QWidget *parent = nullptr);
    ~LoginPage();
    QSqlDatabase getDb();

    QSqlDatabase connectionDataBase();
    //void requestLogin(QSqlDatabase);

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginPage *ui;
    ChatPage * MainChatPage;
    QSqlDatabase db;
    QSqlQuery * query;
    QMessageBox * msg;

};
#endif // LOGINPAGE_H
