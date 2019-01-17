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
    int random_number = rand() % 900;
    enemies * enemy = new enemies(random_number, 0, 1);
    scene()->addItem(enemy);
}

void Player::spawn1(){
    int random_number = rand() % 900;
    enemies * enemy1 = new enemies(random_number, 0, 2);
    scene()->addItem(enemy1);
}

void Player::spawn2(){
    int random_number = rand() % 900;
    enemies * enemy2 = new enemies(random_number, 0, 3);
    scene()->addItem(enemy2);
}
// new spawn, heal object
void Player::spawnHeal(){
    int random_number = rand() % 900;
    enemies * healer = new enemies(random_number, 0, 4);
    scene()->addItem(healer);
}
