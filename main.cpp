#include <QApplication>
#include "game.h"



Game * game;



int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    game = new Game();
    game->show();
    game->prestart();

    return a.exec();
}
