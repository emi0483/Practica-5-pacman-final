#include <QGraphicsPixmapItem>

class moneda
{
public:
    QGraphicsPixmapItem *mon;
    int x,y;
    void aparecer(int x1,int y2);
    bool comer(int obj_x, int obj_y);
};

