#include "moneda.h"

void moneda::aparecer(int x1, int y2){
    x=x1;
    y=y2;
    mon= new QGraphicsPixmapItem;
    mon->setPos(x,y);
    mon->setPixmap(QPixmap(":/new/prefix1/imagenes/moneda.png").scaled(5,5));
}

bool moneda::comer(int obj_x, int obj_y){
    if(x>=obj_x && x<=obj_x+30 && y>=obj_y && y<=obj_y+30){
        delete mon;
        return 1;}
    return 0;
}
