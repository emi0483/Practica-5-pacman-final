#include <QGraphicsPixmapItem>

class moneda
{
public:
    QGraphicsPixmapItem *mon;
    int x,y; //coordenadas
    void aparecer(int x1,int y2); //coordenadas moneda donde queremos
    bool comer(int obj_x, int obj_y); //coordenadas objeto
};

