#include "loginpage/loginpage.h"
#include "chatpage/chatpage.h"//uniquement pour test
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginPage w;
    //ChatPage w;
    w.showFullScreen();
    return a.exec();
}
