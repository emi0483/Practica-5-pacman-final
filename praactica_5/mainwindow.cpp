#include "ui_mainwindow.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) //define el constructor de la case
    : QMainWindow(parent) // Llama al constructor de la clase y entrega al parent como argumento
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); //Inicializa el archivo de diseño 
    escena = new QGraphicsScene; // Se crea una instancia de la clase QGraphicsScene llamada escena. 
    //QGraphicsScene proporciona una superficie 2D en la que se pueden colocar objetos gráficos.
    pac = new QGraphicsPixmapItem; // Hace lo mismo para el pacman
    mapa = new QGraphicsPixmapItem; // hace lo mismo para el mapa
    timer = new QTimer; //Se crean dos instancias de la clase QTimer llamadas timer y timer2. Los objetos QTimer 
    //se utilizan para generar eventos periódicos y se utilizarán para realizar tareas con regularidad en la aplicación
    timer2 = new QTimer;
    timer->stop();
    timer2->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(refrescar()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(mover_pac()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(mover_fan1()));
    //Las  tres lineas anteriores Estas líneas establecen las conexiones de señales y ranuras. Cuando los temporizadores timer y 
    //timer2 alcanzan el tiempo de espera especificado, se emitirá la señal timeout(), que está conectada a las ranuras refrescar(),
    // mover_pac() y mover_fan1() respectivamente.
        
    timer->start(40);
    timer2->start(20);
    //Generar eventos despues de ciertos intervalos de tiempo
        
    ui->graphicsView->setScene(escena);
    pac->setPos(297,436);
    pac->setPixmap(QPixmap(":/new/prefix1/imagenes/pac_man_1.png").scaled(30,30));

    escena->addItem(pac);
    escena->setSceneRect(0,0,624,612);
    crear_fantas();
    mapa->setPos(0,0);
    mapa->setPixmap(QPixmap(":/new/prefix1/imagenes/mapa.png").scaled(624,612)); //OBjeto en las cordenadas
    escena->addItem(mapa);
    cre_par();
    cre_mon();
}

MainWindow::~MainWindow() //destructor de la clase mainwindow
{
    delete timer;
    delete escena;
    delete pac;
    delete red;
    delete pink;
    delete yell;
    delete blue;
    delete mapa;
    delete ui;
}

void MainWindow::mover_pac(){ //Funcion de la clase main window y se encarga de mover el objeto grafico en la escena
    switch(dest){
    case 1: //si dest es igual a 1 se mueve hacia la derecha en incrementos de 3 píxeles si no hay colisión (choque) en esa dirección.
        if(choque(dest,pac))
            pac->setX(pac->x()+3); 
        break;
    case 2://Si dest es igual a 2, el pac se mueve hacia la izquierda en decrementos de 3 píxeles si no hay colisión en esa dirección.
        if(choque(dest,pac))
            pac->setX(pac->x()-3);
        break;
    case 3: //Si dest es igual a 3, el pac se mueve hacia arriba en decrementos de 3 píxeles si no hay colisión en esa dirección.
        if(choque(dest,pac))
            pac->setY(pac->y()-3);
        break;
    case 4: //Si dest es igual a 4, el pac se mueve hacia abajo en incrementos de 3 píxeles si no hay colisión en esa dirección.
        if(choque(dest,pac))
            pac->setY(pac->y()+3);
        break;
    default:
        break;

    }
    ui->label_2->setNum(pac->x());
    ui->label_4->setNum(pac->y());
    if(pac->x()==-50) pac->setX(600);
    else if(pac->x()>600) pac->setX(-50);
    for(im=monedas.begin();im!=monedas.end();im++){
        if((*im).comer(pac->x(),pac->y())){
            monedas.erase(im);
            score++;
        }
    }
    ui->label_6->setNum(score);
//Luego, la función actualiza las etiquetas de label_2 y label_4 con las nuevas coordenadas x e y del pac. Si la posición x del 
//pac es igual a -50, se establece en 600, y si es mayor que 600, se establece en -50. Esto asegura que el pac se mueva a través 
//de los bordes de la escena. Luego, la función verifica si el pac ha colisionado con alguna de las monedas almacenadas en el 
//contenedor monedas. Si ocurre una colisión, se elimina la moneda del contenedor y se incrementa la puntuación score. //Finalmente, la etiqueta label_6 se actualiza con el nuevo valor de score.
}

void MainWindow::keyPressEvent(QKeyEvent *event){ //Encargada de manipular los controles y su funcionamiento
    pac->setTransformOriginPoint(15,15);
    if(event->key()==Qt::Key_D){ //Orienta hacia la derecha
        pac->setRotation(0);
        dest=1;
    }
    else if(event->key()==Qt::Key_A){ //Orienta hacia la izquierda
        pac->setRotation(180);
        dest=2;
    }
    else if(event->key()==Qt::Key_S){ //orienta arriba 
        pac->setRotation(270);
        dest=3;
    }
    else if(event->key()==Qt::Key_Z){ //orienta abajo
        pac->setRotation(90);
        dest=4;
    }
    else if(event->key()==Qt::Key_Space) //NO hay movimiento en ninguna direccion
        dest=0;
}

void MainWindow::refrescar(){ //Cambair las iamgenes de los objetos en estado acutla
    if(estado==1){ 
//Si estado es igual a 1, se establecen las imágenes de pac, red, pink, blue y yell con los archivos de imagen correspondientes 
//a la segunda variante, utilizando la ruta ":/new/prefix1/imagenes/..." y se escala a un tamaño de 30x30 píxeles. Luego, se 
//cambia el valor de estado a 2.
        pac->setPixmap(QPixmap(":/new/prefix1/imagenes/pac_man_2.png").scaled(30,30));
        red->setPixmap(QPixmap(":/new/prefix1/imagenes/fanroj_1.png").scaled(30,30));
        pink->setPixmap(QPixmap(":/new/prefix1/imagenes/fanros_1.png").scaled(30,30));
        blue->setPixmap(QPixmap(":/new/prefix1/imagenes/fanazu_1.png").scaled(30,30));
        yell->setPixmap(QPixmap(":/new/prefix1/imagenes/fanama_1.png").scaled(30,30));
        estado=2;}
    else if (estado==2){
//Si estado es igual a 2, se establecen las imágenes de los objetos gráficos con los archivos de imagen correspondientes a la 
//tercera variante, utilizando la ruta ":/new/prefix1/imagenes/..." y se escala a un tamaño de 30x30 píxeles. 
//Luego, se cambia el valor de estado a 3.
        pac->setPixmap(QPixmap(":/new/prefix1/imagenes/pac_man_3.png").scaled(30,30));
        red->setPixmap(QPixmap(":/new/prefix1/imagenes/fanroj_2.png").scaled(30,30));
        pink->setPixmap(QPixmap(":/new/prefix1/imagenes/fanros_2.png").scaled(30,30));
        blue->setPixmap(QPixmap(":/new/prefix1/imagenes/fanazu_2.png").scaled(30,30));
        yell->setPixmap(QPixmap(":/new/prefix1/imagenes/fanama_2.png").scaled(30,30));
        estado=3;}
    else{
//Si estado no es igual a 1 o 2, se establecen las imágenes de los objetos gráficos con los archivos de imagen
// correspondientes a la primera variante, utilizando la ruta ":/new/prefix1/imagenes/..." y se escala a un tamaño de 30x30 píxeles. 
//Luego, se cambia el valor de estado a 1.
        pac->setPixmap(QPixmap(":/new/prefix1/imagenes/pac_man_1.png").scaled(30,30));
        estado=1;}
}
bool MainWindow::choque(short dest,QGraphicsPixmapItem *obj){ //Verifica si hay una colision entre un objeto grafico y los limites de la 
//escena con los objetos de la lista "pare2"
    bool ban=1;
    int spos[2];
    switch(dest){
    case 1: //Si spos[0] es menor que 24, mayor que 570, menor que 24 o mayor que 560, significa que el objeto obj ha chocado con 
//los límites de la escena y se establece ban en falso.
        spos[0]=obj->x()+2;
        spos[1]=obj->y();
        break;
    case 2:

        spos[0]=obj->x()-2;
        spos[1]=obj->y();
        break;
    case 3:
        spos[0]=obj->x();
        spos[1]=obj->y()-2;
        break;
    case 4:
        spos[0]=obj->x();
        spos[1]=obj->y()+2;
        break;
    }
    if(spos[0]<24 || spos[0]>570 || spos[1]<24 || spos[1]>560)
        ban=0;
    //Se recorre la lista pare2 y se verifica si hay alguna colisión entre el objeto obj y los elementos de la lista. Si se 
//encuentra una colisión, se establece ban en falso.
    for(int i=0;i<pare2.size();i++){
        if(!ban) break;
        ban=!(pare2[i].contacto(spos[0],spos[1],30,30));
//Se recorre la lista pare2 y se verifica si hay alguna colisión entre el objeto obj y los elementos de la lista. 
//Si se encuentra una colisión, se establece ban en falso.
    }
    if(spos[1]>266 && spos[1]<272)
        //Si spos[1] está entre 266 y 272, se establece ban en verdadero. Esta comprobación parece ser una excepción 
//específica en la lógica de colisión.
        ban=1;
    return ban;
}

void MainWindow::crear_fantas(){ // se encarga de crear los objetos gráficos de los fantasmas y agregarlos a la escena.
    red=new QGraphicsPixmapItem; // crea instancia fanastma rojo
    pink=new QGraphicsPixmapItem; //crea la instancia fantasma rosado
    blue=new QGraphicsPixmapItem; //crea la isntancia fantasma azul
    yell=new QGraphicsPixmapItem; //crea la instancia fantasma amarilo 
    red->setPos(254,278); // asigna posicion al fnastama rojo
    red->setPixmap(QPixmap(":/new/prefix1/imagenes/fanroj_1.png").scaled(30,30));//escala el fantasma rojo
    escena->addItem(red); // agrega el fantasma rojo a la escena 
    pink->setPos(284,278); // asigna posicion al fantasma  rosado
    pink->setPixmap(QPixmap(":/new/prefix1/imagenes/fanros_1.png").scaled(30,30));//escala el fastasma rosado
    escena->addItem(pink); //agrega fantasma rosado a la escena
    blue->setPos(314,278); //asigna posicion al fantasma azul
    blue->setPixmap(QPixmap(":/new/prefix1/imagenes/fanazu_1.png").scaled(30,30)); //escala el fantasma azul
    escena->addItem(blue); //agrega el fantasma amarillo a la escena
    yell->setPos(344,278); //asigna posicion al fantasma amarillo
    yell->setPixmap(QPixmap(":/new/prefix1/imagenes/fanama_1.png").scaled(30,30)); //escala el fantasma amarillo
    escena->addItem(yell); //añade el fnatasma amarillo en la escena
}

void MainWindow::mover_fan1(){ 
    bool band=rand()%2;//se crean boolenaos aleatorios
    srand(time(NULL));
//ara cada fantasma, se verifica si no hay una colisión en la dirección actual (mov_fan[i]) o si band es verdadero. 
//En ese caso, se genera una nueva dirección aleatoria para el fantasma correspondiente (mov_fan[i] = 1 + rand() % 4).

//A continuación, se llama a la función mover_fan2() para mover cada fantasma en su dirección correspondiente.
//
    if(!choque(mov_fan[0],red) || band)
        mov_fan[0]=1+rand()%4;
    band=rand()%2;
    if(!choque(mov_fan[1],blue) || band)
        mov_fan[1]=1+rand()%4;
    band=rand()%2;
    if(!choque(mov_fan[2],yell) || band)
        mov_fan[2]=1+rand()%4;
    band=rand()%2;
    if(!choque(mov_fan[3],pink) || band)
        mov_fan[3]=1+rand()%4;
    mover_fan2(mov_fan[0],red);
    mover_fan2(mov_fan[1],blue);
    mover_fan2(mov_fan[2],yell);
    mover_fan2(mov_fan[3],pink);
}

void MainWindow::mover_fan2(short destino,QGraphicsPixmapItem *obj){
//Se utiliza una estructura switch para determinar la dirección (destino) del movimiento del fantasma.
    switch(destino){
    case 1:
        if(choque(destino,obj))
            obj->setX(obj->x()+2);
        break;
    case 2:
        if(choque(destino,obj))
            obj->setX(obj->x()-2);
        break;
    case 3:
        if(choque(destino,obj))
            obj->setY(obj->y()-2);
        break;
    case 4:
        if(choque(destino,obj))
            obj->setY(obj->y()+2);
        break;
    }
//Después del movimiento, se realizan comprobaciones adicionales:


    if(obj->x()>600) obj->setX(-50);//Si la posición x del objeto obj es mayor que 600, se establece la posición x en -50.
    
    else if(obj->x()==-50) obj->setX(600); //Si la posición x del objeto obj es igual a -50, se establece la posición x en 600.
}

void MainWindow::cre_mon(){ //Crea y coloca objetos de monedas en la escena del juego
    moneda a; //crea instancia moneda
    int pos,i=0;
    for(int j=0;j<200;j++) //agrega 200 objetos al vector moenda
        monedas.push_back(a);
    for(pos=40;pos<600;pos+=21){ //este bucle esta para organizar las monedas en diferentes posciones de la escena 
        //se coloca en filas horizontales con una sepracion de 21 pixeles
        if(pos<290 || pos>336){ 
            monedas[i].aparecer(pos,42);//Primero, se colocan monedas en la primera fila (posición y = 42), excepto en el rango 
            //de posiciones 290-336.
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;i++){
        monedas[i].aparecer(pos,110); //Luego, se colocan monedas en la segunda fila (posición y = 110) en incrementos de 21 píxeles.
        escena->addItem(monedas[i].mon);
        pos+=21;}
    for(pos=40;pos<600;pos+=21){
        if(!((pos>163 && pos<211) || (pos>285 && pos<343) || (pos>415 && pos<461))){
            monedas[i].aparecer(pos,170); //A continuación, se colocan monedas en la tercera fila (posición y = 170), excepto 
            //en ciertos rangos de posiciones.
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;pos+=21){
        if(pos<290 || pos>336){
            monedas[i].aparecer(pos,386); //Se repiten estos pasos para las filas restantes (posiciones y = 386, 446, 506, 570).
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;pos+=21){
        if(!((pos>90 && pos<135) || (pos>475 && pos<530)||(pos>290 && pos<336))){
            monedas[i].aparecer(pos,446); //Se repiten estos pasos para las filas restantes (posiciones y = 386, 446, 506, 570).
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;pos+=21){
        if(!((pos>163 && pos<211) || (pos>285 && pos<343) || (pos>415 && pos<461))){
            monedas[i].aparecer(pos,506); //Se repiten estos pasos para las filas restantes (posiciones y = 386, 446, 506, 570).
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;i++){
        monedas[i].aparecer(pos,570); //Se repiten estos pasos para las filas restantes (posiciones y = 386, 446, 506, 570).
        escena->addItem(monedas[i].mon);
        pos+=21;}
    for(pos=60;pos<500;pos+=21){ //Se utiliza otro bucle for para colocar monedas en las columnas verticales con una 
    //separación de 21 píxeles entre ellas.
        if(!((pos>96 && pos<130)||(pos>156 && pos<192)||(pos>362 && pos<408)||(pos>432 && pos<466))){
            monedas[i].aparecer(147,pos); //Primero, se colocan monedas en la columna izquierda (posición x = 147), excepto en 
            //ciertos rangos de posiciones verticales
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=60;pos<500;pos+=21){
        if(!((pos>96 && pos<130)||(pos>156 && pos<192)||(pos>362 && pos<408)||(pos>432 && pos<466))){
            monedas[i].aparecer(470,pos); //Luego, se colocan monedas en la columna derecha (posición x = 470), excepto en 
            //ciertos rangos de posiciones verticales.
            escena->addItem(monedas[i].mon);
            i++;}}
    //Se colocan monedas adicionales en posiciones específicas en la escena.
    monedas[i+1].aparecer(40,138);
    monedas[i+2].aparecer(218,138);
    monedas[i+3].aparecer(395,138);
    monedas[i+4].aparecer(575,138);
    monedas[i+5].aparecer(351,74);
    monedas[i+6].aparecer(265,74);
    monedas[i+7].aparecer(267,414);
    monedas[i+8].aparecer(350,414);
    monedas[i+9].aparecer(217,478);
    monedas[i+10].aparecer(400,478);
    monedas[i+11].aparecer(73,478);
    monedas[i+12].aparecer(540,478);
    monedas[i+13].aparecer(580,536);
    monedas[i+14].aparecer(350,536);
    monedas[i+15].aparecer(267,536);
    for(int j=i+1;j<i+17;j++)
        escena->addItem(monedas[j].mon); //Finalmente, se agregan todas las monedas al escena utilizando el método addItem()
}

void MainWindow::cre_par(){
    paredes a; //se crea la instacia llamada paredes 
    for(int i=0;i<36;i++) //Se utiliza un bucle for para agregar 36 objetos paredes al vector pare2.
        pare2.push_back(a);
    //Se configura cada objeto paredes con las coordenadas y dimensiones correspondientes utilizando el método iniciar(). 
    //Los parámetros de iniciar() representan respectivamente: x, y, ancho y alto de la pared.
    pare2[0].iniciar(60,60,72,36);
    pare2[1].iniciar(168,60,86,36);
    pare2[2].iniciar(290,24,46,72);
    pare2[3].iniciar(372,60,84,36);
    pare2[4].iniciar(492,60,72,36);
    pare2[5].iniciar(60,132,72,24);
    pare2[6].iniciar(168,132,38,132);
    pare2[7].iniciar(242,132,142,24);
    pare2[8].iniciar(420,132,36,132);
    pare2[9].iniciar(492,132,72,24);
    pare2[10].iniciar(290,156,46,72);
    pare2[11].iniciar(206,192,48,36);
    pare2[12].iniciar(372,192,48,36);
    pare2[13].iniciar(24,194,108,72);
    pare2[14].iniciar(492,192,108,72);
    pare2[15].iniciar(242,264,142,60);
    pare2[16].iniciar(25,300,108,72);
    pare2[17].iniciar(166,300,38,72);
    pare2[18].iniciar(418,300,38,72);
    pare2[19].iniciar(490,300,108,72);
    pare2[20].iniciar(240,360,142,12);
    pare2[21].iniciar(288,372,46,60);
    pare2[22].iniciar(58,408,72,24);
    pare2[23].iniciar(166,408,86,24);
    pare2[24].iniciar(370,408,84,24);
    pare2[25].iniciar(490,408,72,24);
    pare2[26].iniciar(94,432,36,60);
    pare2[27].iniciar(490,432,36,60);
    pare2[28].iniciar(24,468,34,24);
    pare2[29].iniciar(166,468,36,60);
    pare2[30].iniciar(238,468,148,24);
    pare2[31].iniciar(420,268,36,60);
    pare2[32].iniciar(562,468,38,24);
    pare2[33].iniciar(58,528,194,24);
    pare2[34].iniciar(288,492,46,60);
    pare2[35].iniciar(370,528,194,24);
}

void MainWindow::ganar(){ //En la función ganar(), se muestra un cuadro de diálogo QMessageBox con el mensaje "Ganaste".
    QMessageBox mensaje;
    mensaje.setText("Ganaste");
    mensaje.exec();
}

