#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QFile>

class enemies: public QObject,public QGraphicsRectItem{
  Q_OBJECT
public:

    enemies(int x, int y, int width, int height, QBrush colour, int rotateAngle, int acceleration);

    //public attributes
    QTimer * timer1;
    int rotateAngle;
    int acceleration;
    int lastX;
    int lastY;

public slots:
    void move();
    void stop();
    void resume();
    void save(QFile &file);
    void load(QFile &file);
};

class enemies1: public QObject,public QGraphicsEllipseItem{
  Q_OBJECT
public:

    enemies1();

    //public attributes
    QTimer * timer1;
    int lastX;
    int lastY;

public slots:
    void move();
    void stop();
    void resume();
    void save(QFile &file);
    void load(QFile &file);
};

class enemies2: public QObject,public QGraphicsRectItem{
  Q_OBJECT
public:

    enemies2();

    //public attributes
    QTimer * timer1;
    int lastX;
    int lastY;

public slots:
    void move();
    void stop();
    void resume();
    void save(QFile &file);
    void load(QFile &file);
};




