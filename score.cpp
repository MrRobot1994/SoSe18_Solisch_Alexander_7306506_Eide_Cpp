#include "score.h"
#include <QFont>
#include "game.h"
#include <QTime>
#include <QCoreApplication>

extern Game * game;

score::score(QGraphicsItem *parent) : QGraphicsTextItem(parent){
    //score bei 0 initialisieren
    //score1 = 3;
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


