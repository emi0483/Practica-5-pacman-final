#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include "QPixmap"
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <stdlib.h>
#include <time.h>
#include "paredes.h"
#include "moneda.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void keyPressEvent(QKeyEvent *event); // Esta es una función de evento que se invoca cuando se presiona una tecla. 
    //Puede ser sobrescrita en la clase derivada para manejar eventos de teclado específicos.
    MainWindow(QWidget *parent = nullptr);//Constructor de la clase MainWindow que toma un puntero a un objeto 
    //QWidget como parámetro. El parámetro parent se establece como nullptr por defecto, lo que indica que no hay un objeto 
    //principal padre para esta ventana.
    ~MainWindow(); //Destructor de la clase

private slots:
    void mover_pac(); //funcion mover pacman
    void refrescar(); //refresaca la escena de
    void mover_fan1(); //funcion move fantasmas

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena; //Puntero a un objeto QGraphicsScene, que representa la escena del juego donde se colocan los elementos gráficos.
    QGraphicsPixmapItem *pac,*red,*blue,*yell,*pink,*mapa; // Punteros a objetos QGraphicsPixmapItem, que representan los elementos gráficos 
    //en el juego, como los personajes (Pacman y fantasmas) y el mapa.
    QTimer *timer,*timer2;//Punteros a objetos QTimer, que se utilizan para controlar el tiempo en el juego y 
    //activar ciertas acciones en intervalos regulares.
    QVector <paredes> pare2;//Un vector de objetos paredes, utilizado para almacenar y gestionar las paredes del juego.
    QVector <moneda> monedas; //Un vector de objetos moneda, utilizado para almacenar y gestionar las monedas del juego.
    QVector <moneda>::iterator im; // Un iterador para recorrer los elementos del vector de monedas.
    void crear_fantas(); //funcion crear fantasmas
    void mover_fan2(short destino,QGraphicsPixmapItem *obj); //Una función que se utiliza para mover un fantasma a una posición de destino 
    //específica en la escena.
    bool choque(short destino,QGraphicsPixmapItem *obj); //Una función que comprueba si hay una colisión entre un objeto (fantasma o 
    //Pacman) y las paredes del juego.
    void cre_par(); //funcion crear pacman
    void cre_mon(); //funcion crear moneda
    void ganar(); //funcion para ganar
    short estado=1,dest=0,mov_fan[4]={1,2,3,4},score=0; //Variables miembro de la clase que se utilizan para controlar
// el estado del juego, la dirección y el movimiento de los fantasmas, y la puntuación del jugador, respectivamente.
};
#endif // MAINWINDOW_H
