#include <QGraphicsRectItem>
#include <QObject>

class liveIcon:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    void deleteIcon();
};


