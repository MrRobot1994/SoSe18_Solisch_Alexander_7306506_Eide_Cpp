#include "score.h"
#include <QFont>
#include "game.h"
#include <QTime>
#include <QCoreApplication>

extern Game * game;

score::score(QGraphicsItem *parent) : QGraphicsTextItem(parent){
    //score bei 0 initialisieren
    punkte = 0;

    //Text abbilden
    setPlainText(QString("Score: ") + QString::number(punkte));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));

}

void score::increase(){
    punkte++;
    setPlainText(QString("Score: ") + QString::number(punkte)); // Score: 1
}


int score::getPunkte(){

    return punkte;

}

void score::setPunkte(int _punkte){

    this->punkte = _punkte;
    setPlainText(QString("Score: ") + QString::number(_punkte));

}


