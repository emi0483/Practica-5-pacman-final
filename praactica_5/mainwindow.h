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
    void keyPressEvent(QKeyEvent *event);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mover_pac(); //funcion mover pacman
    void refrescar(); 
    void mover_fan1(); //funcion move fantasmas

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;
    QGraphicsPixmapItem *pac,*red,*blue,*yell,*pink,*mapa;
    QTimer *timer,*timer2;
    QVector <paredes> pare2;
    QVector <moneda> monedas;
    QVector <moneda>::iterator im;
    void crear_fantas(); //funcion crear fantasmas
    void mover_fan2(short destino,QGraphicsPixmapItem *obj);
    bool choque(short destino,QGraphicsPixmapItem *obj);
    void cre_par(); //funcion crear pacman
    void cre_mon(); //funcion crear moneda
    void ganar(); //funcion para ganar
    short estado=1,dest=0,mov_fan[4]={1,2,3,4},score=0;
};
#endif // MAINWINDOW_H
