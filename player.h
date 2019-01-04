#include <QGraphicsRectItem>
#include <QObject>

class Player:public QObject, public QGraphicsRectItem {
    Q_OBJECT
  public:
    void keyPressEvent(QKeyEvent * event);

public slots:
    void spawn();
    void spawn1();
    void spawn2();
    void spawnHeal();
};


