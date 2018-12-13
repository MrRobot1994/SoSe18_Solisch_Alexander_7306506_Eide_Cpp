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
    enemies * enemy = new enemies(0, 30, 20, 20, Qt::darkCyan, 10, 5);
    scene()->addItem(enemy);
}

void Player::spawn1(){

    enemies * enemy1 = new enemies(0, 30, 25, 25, Qt::yellow, 2, 10);
    scene()->addItem(enemy1);
}

void Player::spawn2(){

    enemies * enemy2 = new enemies(0, 30, 40, 40, Qt::darkYellow, 0, 2);
    scene()->addItem(enemy2);
}



