#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> //random integer
#include <QDebug>
#include <windows.h>
#include <QApplication>
#include "game.h"
#include "enemies.h"
#include "button.h"

extern Game * game;

enemies::enemies(int x, int y, int width, int height, QBrush colour, int _rotateAngle, int _acceleration):QObject(),QGraphicsRectItem(){

    //set random position
    int random_number = rand() % 900;
    setPos(random_number,0);

    //draw the rect
    setRect(x,y,width,height);
    setBrush(colour);

    rotateAngle = _rotateAngle;
    acceleration = _acceleration;

    //connect
    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(move()));
    timer1->start(50);

//SLOT stop() mit Stopbutton verbunden (in game.cpp)
connect(game->stopbutton,SIGNAL(clicked()),SLOT(stop()));
//SLOT stop() mit Resumebutton verbunden (in game.cpp)
connect(game->resumebutton,SIGNAL(clicked()),SLOT(resume()));
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

            //decreaselive the score
            game->health1->decreaseLive();

            //löschen von liveicon
            game->liveIcon1->deleteIcon();

            //game->stopbutton->clicked();
            //Sleep(1000);
            //game->resumebutton->clicked();

            //Freeze

            game->stop();

            Sleep(1000);

            game->resume();

            //remove enemy
            scene()->removeItem(this);

            //delete enemie
            delete this;

            //anwendung beenden, wenn der counter größer als 4ist
            if( i>4){
             game = new Game();
            }

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

void enemies::stop(){
    //stop den timer für enemy bewegung
    timer1->stop();
}

void enemies::resume(){
    //startet timer wieder für enemy bewegung
    timer1->start();
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
