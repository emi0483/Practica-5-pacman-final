#include "paredes.h"

void paredes::iniciar(int x_par, int y_par, int an_par, int al_par){
    x=x_par;
    y=y_par;
    ancho=an_par;
    alto=al_par;
}

bool paredes::contacto(int x_obj, int y_obj, int an_obj, int al_obj){
    bool temp;
    for(int i=y;i<(y+alto);i++){
        temp=(i>=y_obj && i<=(y_obj+al_obj));
        for(int j=x;j<(x+ancho);j++){
            if(temp && j>=x_obj && j<=(x_obj+an_obj))
                return 1;
        }
    }
    return 0;
}
