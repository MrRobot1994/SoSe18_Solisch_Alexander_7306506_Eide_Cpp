#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> //random integer
#include <QDebug>
#include <QApplication>
#include "game.h"
#include "enemies.h"
#include "button.h"

extern Game * game;

enemies::enemies(int x, int y, int _enemyType):QObject(),QGraphicsRectItem(){

    this->enemyType = _enemyType;

    int width;
    int height;
    QBrush colour;

    if (enemyType == 1) {
        width = 20;
        height= 20;
        colour= Qt::darkCyan;
        rotateAngle= 3; //10
        acceleration= 5;

    } else if (enemyType == 2) {
        width = 25;
        height=25;
        colour= Qt::yellow;
        rotateAngle= 2;
        acceleration= 10;
    } else if (enemyType == 3) {
        width = 40;
        height= 40;
        colour= Qt::darkYellow;
        rotateAngle= 0;
        acceleration= 2;
    } else if (enemyType == 4) {
        width = 30;
        height= 30;
        colour= Qt::green;
        rotateAngle= 1;
        acceleration= 4;
    }

    //set random position
    setPos(x,y);

    //draw the rect
    setRect(0,30,width,height);
    setBrush(colour);

    //connect
    moveTimer = new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(50);

//SLOT stop() mit Stopbutton verbunden (in game.cpp)
// connect(game->stopbutton,SIGNAL(clicked()),SLOT(pause()));
//SLOT save() mit Savebutton verbunden (in game.cpp)
//connect(gamee->savebutton,SIGNAL(clicked()),SLOT(save()));
//SLOT load() mit Loadbutton verbunden (in game.cpp)
//connect(gamee->loadbutton,SIGNAL(clicked()),SLOT(load()));
}

void enemies::move(){

    //if enemie collides with player, destroy enemie
    QList<QGraphicsItem * > colliding_items = collidingItems();

    for(int i=0, n = colliding_items.size();i<n; i++){
        if(typeid(*(colliding_items[i])) ==  typeid(Player)){

            //remove enemy
            scene()->removeItem(this);

            if (this->getType() == 4) {
                game->health1->increaseLive();
            } else {
                //decreaselive the score
                game->health1->decreaseLive();
            }

            //delete enemie
            delete this;

            return;
        }
    }

    //move enemies down
    int angle = rotateAngle ? y() + rotateAngle : 0;

    setRotation(angle);
    setPos(x(),y()+acceleration);
        if (pos().y() > 600){
            //increase the score
            //gamee->health1->increaseScore();
            scene()->removeItem(this);
            delete this;
        }
}

void enemies::pause(){
    if(moveTimer->isActive()){
        this->stop();
    }
    else{
        this->resume();
    }
}

void enemies::stop(){
    //stop den timer für enemy bewegung
    moveTimer->stop();
}

void enemies::resume(){
    //startet timer wieder für enemy bewegung
    moveTimer->start();
}


//Funktionen Speichern und Laden
//Positionen werden gespeichert
//LastX und LastY werden für die Koordinaten gebraucht
//für das Savegame in game.cpp
void enemies::save(QFile &file){

    QTextStream out(&file);
    out >> lastX >> endl;
    out >> lastY >> endl;
}

void enemies::load(QFile &file){

    QTextStream in(&file);
        int x,y;
        in >> x << endl;
        in >> y << endl;
        lastX=x;
        lastY=y;
        update();
}

int enemies::getType() {
    return enemyType;
}
