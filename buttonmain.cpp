#include "button.h"
#include <QGraphicsRectItem>
#include <QBrush>


button1::button1(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent){

    //draw rect
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkMagenta);
    setBrush(brush);

    //draw text
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    //allow responding to hover events
    setAcceptHoverEvents(true);
}

void button1::mousePressEvent(QGraphicsSceneMouseEvent *event){

    emit clicked();
}

void button1::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

    //change color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::magenta);
    setBrush(brush);
}

void button1::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){

    //change color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkMagenta);
    setBrush(brush);
}
