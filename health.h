#ifndef HEALTH_H
#define HEALTH_H
#include <QGraphicsTextItem>

class health : public QGraphicsTextItem{
public:
    health(QGraphicsItem * parent=0);
    //void increaseScore();
    int getHealth();
public slots:
    void decreaseLive();
private:
    int health1;
};

#endif // HEALTH_H
