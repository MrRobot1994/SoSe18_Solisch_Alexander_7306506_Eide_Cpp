#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "score.h"
#include "health.h"
#include "liveicon.h"
#include <QFile>
#include <QTimer>
#include <QGraphicsRectItem>
#include "button.h"
#include <QGraphicsTextItem>

class Game : public QGraphicsView{
    Q_OBJECT

public:
   Game(QWidget * parent=NULL);

    //public methods
        void restart();
        void prestart();
        void stop(bool freeze = true);
        void resume();

    //public attributs
    QGraphicsScene * scene;
    QGraphicsTextItem * title;
    Player * player;
    score * punkte;
    health * health1;
    liveIcon * liveIcon1;
    liveIcon * liveIcon2;
    liveIcon * liveIcon3;
    QTimer * timer;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timerHeal;
    QTimer * Scoretimer;
    button * startbutton;
    button1 * startbuttonmain;
    button1 * quitbuttonmain;
    button1 * loadmain;
    button * stopbutton;
    button * loadbutton;
    button * savebutton;
    button * quit;

public slots:
     void start();
     void load();
     void loadRestart();
     void save();
     void pause();
};


