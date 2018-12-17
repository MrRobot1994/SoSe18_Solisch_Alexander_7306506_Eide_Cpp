#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class button :public QObject, public QGraphicsRectItem{
   Q_OBJECT
public:

    button(QString name, QGraphicsItem * parent = NULL);
    void setText(QString newText);

    //public methods
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:

    void clicked();

private:

    QGraphicsTextItem* text;
};



class button1 :public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    button1(QString name, QGraphicsItem * parent = NULL);

    //public methods
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:

    void clicked();

private:

    QGraphicsTextItem* text;
};
#endif // BUTTON_H
