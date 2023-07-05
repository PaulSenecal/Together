#include "loginpage/loginpage.h"
#include "chatpage/chatpage.h"//uniquement pour test
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatPage w;
    w.show();
    return a.exec();
}
