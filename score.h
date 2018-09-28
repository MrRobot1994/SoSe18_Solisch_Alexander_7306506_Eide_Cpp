#ifndef SCORE_H
#define SCORE_H
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>

class score : public QGraphicsTextItem{
    Q_OBJECT
public:
    score(QGraphicsItem * parent=0);
    int getPunkte();

    QTimer * Scoretimer;

public slots:

    void increase();

private:
    int punkte;

};
#endif // SCORE_H

