#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QFile>

class enemies: public QObject,public QGraphicsRectItem{
  Q_OBJECT
public:

    enemies(int x, int y, int type);

    //public attributes
    QTimer * moveTimer;
    int rotateAngle;
    int acceleration;
    int lastX;
    int lastY;
    int getType();

public slots:
    void move();
    void stop();
    void resume();
    void pause();
    void save(QFile &file);
    void load(QFile &file);

private:
    int enemyType;
};
