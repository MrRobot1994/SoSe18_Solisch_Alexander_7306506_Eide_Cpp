#include "player.h"
#include <QKeyEvent>
#include "enemies.h"
#include <QGraphicsScene>


void Player::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left){
        if (pos().x() > 90)
        setPos(x()-10,y());
    }
    if(event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
        setPos(x()+10,y());
    }
}

void Player::spawn(){
    //schaffung des enemy
    enemies * enemy = new enemies();
    scene()->addItem(enemy);
}

void Player::spawn1(){

    enemies1 * enemy1 = new enemies1();
    scene()->addItem(enemy1);
}

void Player::spawn2(){

    enemies2 * enemy2 = new enemies2();
    scene()->addItem(enemy2);
}



