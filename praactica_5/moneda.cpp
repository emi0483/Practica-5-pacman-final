#include "moneda.h"

void moneda::aparecer(int x1, int y2){ //metodo para mostrar moneda en la posicion que queremos
    x=x1; //coordenada x
    y=y2; //coordenada y
    mon= new QGraphicsPixmapItem; //creamos objeto
    mon->setPos(x,y); //le damos la posicion
    mon->setPixmap(QPixmap(":/new/prefix1/imagenes/moneda.png").scaled(5,5)); //cargamos la imagen y le damos 5x5 pixeles
}

bool moneda::comer(int obj_x, int obj_y){ //metodo pa comer moneda
    //si las coordenadas xy de la moneda estan en el rango del objeto de 30pixeles
    if(x>=obj_x && x<=obj_x+30 && y>=obj_y && y<=obj_y+30){ 
        delete mon; //eliminamos moneda
        return 1;} //moneda ha sido comida
    return 0; //no se ha comido
}
