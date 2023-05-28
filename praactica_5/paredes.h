

class paredes
{
public:
    void iniciar(int x_par,int y_par,int an_par,int al_par); //coordenadas y dimensiones pared
    bool contacto(int x_obj,int y_obj,int an_obj,int al_obj); //coordenadas y dimensiones objeto
    int x,y,ancho,alto;
};

