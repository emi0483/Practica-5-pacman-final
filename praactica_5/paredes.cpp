#include "paredes.h"

void paredes::iniciar(int x_par, int y_par, int an_par, int al_par){ //metodo de la clase paredes para coordenadas y dimensiones de una pared
    x=x_par; //coordenada x
    y=y_par; //coordenada y
    ancho=an_par; //ancho
    alto=al_par; //alto
}

bool paredes::contacto(int x_obj, int y_obj, int an_obj, int al_obj){ //metodo para saber si se colisiona con una pared
    bool temp;
    for(int i=y;i<(y+alto);i++){ //pixeles que forman la pared
        temp=(i>=y_obj && i<=(y_obj+al_obj)); //comparamos las iteraciones del for con las coordenadas del objeto
        for(int j=x;j<(x+ancho);j++){ //lo mismo pero con ancho
            if(temp && j>=x_obj && j<=(x_obj+an_obj))
                return 1; //hay colision
        }
    }
    return 0; //no hay colision
}
