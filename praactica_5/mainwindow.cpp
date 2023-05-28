#include "ui_mainwindow.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    escena = new QGraphicsScene;
    pac = new QGraphicsPixmapItem;
    mapa = new QGraphicsPixmapItem;
    timer = new QTimer;
    timer2 = new QTimer;
    timer->stop();
    timer2->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(refrescar()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(mover_pac()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(mover_fan1()));
    timer->start(40);
    timer2->start(20);
    ui->graphicsView->setScene(escena);
    pac->setPos(297,436);
    pac->setPixmap(QPixmap(":/new/prefix1/imagenes/pac_man_1.png").scaled(30,30));
    escena->addItem(pac);
    escena->setSceneRect(0,0,624,612);
    crear_fantas();
    mapa->setPos(0,0);
    mapa->setPixmap(QPixmap(":/new/prefix1/imagenes/mapa.png").scaled(624,612));
    escena->addItem(mapa);
    cre_par();
    cre_mon();
}

MainWindow::~MainWindow()
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

void MainWindow::mover_pac(){
    switch(dest){
    case 1:
        if(choque(dest,pac))
            pac->setX(pac->x()+3);
        break;
    case 2:
        if(choque(dest,pac))
            pac->setX(pac->x()-3);
        break;
    case 3:
        if(choque(dest,pac))
            pac->setY(pac->y()-3);
        break;
    case 4:
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
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    pac->setTransformOriginPoint(15,15);
    if(event->key()==Qt::Key_D){
        pac->setRotation(0);
        dest=1;
    }
    else if(event->key()==Qt::Key_A){
        pac->setRotation(180);
        dest=2;
    }
    else if(event->key()==Qt::Key_W){
        pac->setRotation(270);
        dest=3;
    }
    else if(event->key()==Qt::Key_S){
        pac->setRotation(90);
        dest=4;
    }
    else if(event->key()==Qt::Key_Space)
        dest=0;
}

void MainWindow::refrescar(){
    if(estado==1){
        pac->setPixmap(QPixmap(":/new/prefix1/imagenes/pac_man_2.png").scaled(30,30));
        red->setPixmap(QPixmap(":/new/prefix1/imagenes/fanroj_1.png").scaled(30,30));
        pink->setPixmap(QPixmap(":/new/prefix1/imagenes/fanros_1.png").scaled(30,30));
        blue->setPixmap(QPixmap(":/new/prefix1/imagenes/fanazu_1.png").scaled(30,30));
        yell->setPixmap(QPixmap(":/new/prefix1/imagenes/fanama_1.png").scaled(30,30));
        estado=2;}
    else if (estado==2){
        pac->setPixmap(QPixmap(":/new/prefix1/imagenes/pac_man_3.png").scaled(30,30));
        red->setPixmap(QPixmap(":/new/prefix1/imagenes/fanroj_2.png").scaled(30,30));
        pink->setPixmap(QPixmap(":/new/prefix1/imagenes/fanros_2.png").scaled(30,30));
        blue->setPixmap(QPixmap(":/new/prefix1/imagenes/fanazu_2.png").scaled(30,30));
        yell->setPixmap(QPixmap(":/new/prefix1/imagenes/fanama_2.png").scaled(30,30));
        estado=3;}
    else{
        pac->setPixmap(QPixmap(":/new/prefix1/imagenes/pac_man_1.png").scaled(30,30));
        estado=1;}
}
bool MainWindow::choque(short dest,QGraphicsPixmapItem *obj){
    bool ban=1;
    int spos[2];
    switch(dest){
    case 1:
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
    for(int i=0;i<pare2.size();i++){
        if(!ban) break;
        ban=!(pare2[i].contacto(spos[0],spos[1],30,30));
    }
    if(spos[1]>266 && spos[1]<272)
        ban=1;
    return ban;
}

void MainWindow::crear_fantas(){
    red=new QGraphicsPixmapItem;
    pink=new QGraphicsPixmapItem;
    blue=new QGraphicsPixmapItem;
    yell=new QGraphicsPixmapItem;
    red->setPos(254,278);
    red->setPixmap(QPixmap(":/new/prefix1/imagenes/fanroj_1.png").scaled(30,30));
    escena->addItem(red);
    pink->setPos(284,278);
    pink->setPixmap(QPixmap(":/new/prefix1/imagenes/fanros_1.png").scaled(30,30));
    escena->addItem(pink);
    blue->setPos(314,278);
    blue->setPixmap(QPixmap(":/new/prefix1/imagenes/fanazu_1.png").scaled(30,30));
    escena->addItem(blue);
    yell->setPos(344,278);
    yell->setPixmap(QPixmap(":/new/prefix1/imagenes/fanama_1.png").scaled(30,30));
    escena->addItem(yell);
}

void MainWindow::mover_fan1(){
    bool band=rand()%2;
    srand(time(NULL));
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
    if(obj->x()>600) obj->setX(-50);
    else if(obj->x()==-50) obj->setX(600);
}

void MainWindow::cre_mon(){
    moneda a;
    int pos,i=0;
    for(int j=0;j<200;j++)
        monedas.push_back(a);
    for(pos=40;pos<600;pos+=21){
        if(pos<290 || pos>336){
            monedas[i].aparecer(pos,42);
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;i++){
        monedas[i].aparecer(pos,110);
        escena->addItem(monedas[i].mon);
        pos+=21;}
    for(pos=40;pos<600;pos+=21){
        if(!((pos>163 && pos<211) || (pos>285 && pos<343) || (pos>415 && pos<461))){
            monedas[i].aparecer(pos,170);
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;pos+=21){
        if(pos<290 || pos>336){
            monedas[i].aparecer(pos,386);
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;pos+=21){
        if(!((pos>90 && pos<135) || (pos>475 && pos<530)||(pos>290 && pos<336))){
            monedas[i].aparecer(pos,446);
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;pos+=21){
        if(!((pos>163 && pos<211) || (pos>285 && pos<343) || (pos>415 && pos<461))){
            monedas[i].aparecer(pos,506);
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=40;pos<600;i++){
        monedas[i].aparecer(pos,570);
        escena->addItem(monedas[i].mon);
        pos+=21;}
    for(pos=60;pos<500;pos+=21){
        if(!((pos>96 && pos<130)||(pos>156 && pos<192)||(pos>362 && pos<408)||(pos>432 && pos<466))){
            monedas[i].aparecer(147,pos);
            escena->addItem(monedas[i].mon);
            i++;}}
    for(pos=60;pos<500;pos+=21){
        if(!((pos>96 && pos<130)||(pos>156 && pos<192)||(pos>362 && pos<408)||(pos>432 && pos<466))){
            monedas[i].aparecer(470,pos);
            escena->addItem(monedas[i].mon);
            i++;}}
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
        escena->addItem(monedas[j].mon);
}

void MainWindow::cre_par(){
    paredes a;
    for(int i=0;i<36;i++)
        pare2.push_back(a);
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

void MainWindow::ganar(){
    QMessageBox mensaje;
    mensaje.setText("Ganaste");
    mensaje.exec();
}

