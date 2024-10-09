#ifndef CHATPAGE_H
#define CHATPAGE_H
#include "clientsocket.h"
#include <QWidget>
#include <QSoundEffect>
#include <QTextEdit>
#include <QInputDialog>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();
    void setNom(QString);
    void adminAccess(QString);
    QSoundEffect *start;
    QSoundEffect *hover;
    int getSounds();
    int getSoundh();
    void setSounds(int);
    void setSoundh(int);
    bool checkFriendInDB(const QString &friendName);
    void afficherAmi(const QString &friendName);
    bool connectToDatabase();
    QSqlDatabase db;

private slots:
    void on_sendMessageQpushButton_clicked();
    void on_pushButton_clicked();
    void afficherMessage(QByteArray);
    void on_goToChatQpushButton_clicked(bool isSelected);
    void on_goToGroupQPushButton_clicked();
    void on_addFriendQPushButton_clicked();

private:
    Ui::ChatPage *ui;
    ClientSocket client;
    bool connection=false;
    bool isSelected = 1;
    int sounds;
    int soundh;
    QTextEdit *addFriend;
};

#endif // CHATPAGE_H
