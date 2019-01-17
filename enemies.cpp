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
//A lot changed in here, created enemy types instead of multiple cpp enemy files

enemies::enemies(int x, int y, int _enemyType):QObject(),QGraphicsRectItem(){

    this->enemyType = _enemyType;

    int width;
    int height;
    QBrush colour;
//declaration of types, type 4 is the healer
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

}

void enemies::move(){

    //if enemie collides with player, destroy enemie
    QList<QGraphicsItem * > colliding_items = collidingItems();

    for(int i=0, n = colliding_items.size();i<n; i++){
        if(typeid(*(colliding_items[i])) ==  typeid(Player)){

            //remove enemy
            scene()->removeItem(this);
// increase life if you hit the healer, else decrease life if you hit the enemy, delete both healer an enemy
            if (this->getType() == 4) {
                game->health1->increaseLive();
            } else {
                //decreaselive the score
                game->health1->decreaseLive();
            }

            //delete enemie/healer
            delete this;

            return;
        }
    }

    //move enemies down
    int angle = rotateAngle ? y() + rotateAngle : 0;

    setRotation(angle);
    setPos(x(),y()+acceleration);
        if (pos().y() > 600){
            scene()->removeItem(this);
            delete this;
        }
}

//pause the movement of the enemies if the button pause is clicked, resume if it's klicked again
void enemies::pause(){
    if(moveTimer->isActive()){
        this->stop();
    }
    else{
        this->resume();
    }
}

//stops enemies movement
void enemies::stop(){
    //stop den timer für enemy bewegung
    moveTimer->stop();
}
// resumes enemies movement
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
