#include <QApplication>

#include "server.h"



int main(int argc, char* argv[])

{
    QApplication app(argc, argv);



    serverwin fenetre; //on créé une instance de l'objet serverwin

    fenetre.show(); //et on l'affiche



    return app.exec();

}
