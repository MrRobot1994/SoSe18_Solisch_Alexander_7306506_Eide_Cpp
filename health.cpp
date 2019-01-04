#include "health.h"
#include "game.h"
#include "enemies.h"
#include <QFont>
#include <QTime>
#include <QGraphicsTextItem>


extern Game * game;

health::health(QGraphicsItem *parent) : QGraphicsTextItem(parent){

    //health1 bei 3 initialisieren
    health1 = 3;

    //text abbilden
    setPlainText(QString("Health: "));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
    setPos(0,25);
}

void health::decreaseLive(){

    health1--;

    if(health1==2){
        game->liveIcon3->setBrush(Qt::darkGray);
        game->player->setOpacity(0.6);
        //Freeze game and resume because game not over
        game->stop();
        game->resume();
    }

    if(health1==1){
        game->liveIcon2->setBrush(Qt::darkGray);
        game->player->setOpacity(0.3);
        //Freeze game and resume because game not over
        game->stop();
        game->resume();
    }

    if(health1==0){
        game->liveIcon1->setBrush(Qt::darkGray);
        game->player->hide();

        // Freeze game but dont resume because game is over
        game->stop();

        // Delete remaining enemies
        QList<QGraphicsItem*> sceneItems = game->scene->items();
        for(QGraphicsItem* item : sceneItems) {
            enemies* enemy = dynamic_cast<enemies*>(item);
            if (enemy == NULL) {
                continue;
            }
            game->scene->removeItem(enemy);
            delete enemy;
        }

        //load game menu after death

        int finalScore = game->punkte->getPunkte();
        game->title = new QGraphicsTextItem(QString("Game Over! You scored ") + QString::number(finalScore) + QString(" points!"));
        QFont titleFont("comic sans",25);
        game->title->setFont(titleFont);
        int txPos = game->width()/2 - game->title->boundingRect().width()/2;
        int tyPos = 100;
        game->title->setPos(txPos,tyPos);
        game->scene->addItem(game->title);

        game->scene->addItem(game->startbuttonmain);
        game->scene->addItem(game->quitbuttonmain);
        game->scene->addItem(game->loadmain);

    }

}

void health::increaseLive(){

    if (health1 >= 3) {
        return;
    }

    health1++;

    if(health1==3){
        game->liveIcon3->setBrush(Qt::magenta);
        game->player->setOpacity(1);
        //Freeze game and resume because game not over
        game->stop();
        game->resume();
    }

    if(health1==2){
        game->liveIcon2->setBrush(Qt::magenta);
        game->player->setOpacity(0.6);
        //Freeze game and resume because game not over
        game->stop();
        game->resume();
    }
}

int health::getHealth(){

      return health1;
}

void health::setHealth( int _health){

    this->health1 = _health;
    if (_health == 1) {
        game->liveIcon1->setBrush(Qt::magenta);
        game->liveIcon2->setBrush(Qt::darkGray);
        game->liveIcon3->setBrush(Qt::darkGray);
        game->player->setOpacity(0.3);
    } else if (_health == 2) {
        game->liveIcon1->setBrush(Qt::magenta);
        game->liveIcon2->setBrush(Qt::magenta);
        game->liveIcon3->setBrush(Qt::darkGray);
        game->player->setOpacity(0.6);
    } else if (_health == 3) {
        game->liveIcon1->setBrush(Qt::magenta);
        game->liveIcon2->setBrush(Qt::magenta);
        game->liveIcon3->setBrush(Qt::magenta);
        game->player->setOpacity(1);
    }
}

