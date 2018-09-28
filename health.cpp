#include "health.h"
#include "game.h"
#include <QFont>
#include <QTime>


extern Game * game;

health::health(QGraphicsItem *parent) : QGraphicsTextItem(parent){

    //health1 bei 3 initialisieren
    health1 = 3;

    //text abbilden
    setPlainText(QString("Health: "));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void health::decreaseLive(){

    health1--;

    if(health1==2){
    game->liveIcon3->setBrush(Qt::darkGray);
    //gamee->player->setRect(0,0,120,25);
    game->player->setOpacity(0.6);

    }

    if(health1==1){
        game->liveIcon2->setBrush(Qt::darkGray);
        game->player->setOpacity(0.3);
    }

    if(health1==0){
        game->liveIcon1->setBrush(Qt::darkGray);
        game->player->hide();


        game->timer->stop();
        game->timer1->stop();
        game->timer2->stop();


        //load game menu after death
        game->scene->addItem(game->startbuttonmain);
        game->scene->addItem(game->quitbuttonmain);
        game->scene->addItem(game->loadmain);

    }

}

int health::getHealth(){

      return health1;
}

