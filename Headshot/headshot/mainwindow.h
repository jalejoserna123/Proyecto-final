#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define PI 3.141592654
#define RUTA_ARCHIVO "objetivos.txt"     //ruta en que se encuentra el archivo de objetivos
#define RUTA_ARCHIVO_2 "obstaculos.txt"     //ruta en que se encuentra el archivo de obstaculos


#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QTimer>
#include <QFile>
#include "proyector.h"
#include "proyectorgraf.h"
#include "proyectil.h"
#include "proyectilgraf.h"
#include "objetivo.h"
#include "objetivograf.h"
#include "obstaculo.h"
#include "obstaculograf.h"
#include <time.h>
#include <math.h>
#include <QMouseEvent>
#include <fstream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void actualizar();

    void power();

    void on_pushButton_multijugador_clicked();

    void on_pushButton_guardar_partida_clicked();

    void on_pushButton_cargar_partida_clicked();

    void on_pushButton_reiniciar_nivel_clicked();

    void on_pushButton_Individual_clicked();

    void on_pushButton_reiniciar_juego_clicked();

    void on_pushButton_sound_clicked();

protected:

    bool eventFilter(QObject* object, QEvent* event) override;
    //void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    int h_limit;
    int v_limit;
    int vel;
    int i=20, j = 200;
    float dt;
    float delta=0;
    int cantidad =0;
    int puntuacion=0;
    int acumulado=0;
    int cont = 0;
    void bordercollision(proyectilGraf *b);   //metodo para las colisiones con los bordes del mundo
    void loader(int ban);
    void changeMap();
    void multijugador();
    QList<proyectorGraf*> proyector;
    QList<proyectilGraf*> proyectiles;
    QList<objetivoGraf*> objetivos;
    QList<objetivoGraf*> temp_objetivos;
    QList<obstaculoGraf*> obstaculos;
    QList<QString> punt_jugadores;
    QList<obstaculoGraf*> guias;
    QGraphicsScene* scene;
    QGraphicsTextItem *texto;
    QGraphicsTextItem *vida;
    QGraphicsTextItem *mensaje;
    QTimer* timer;
    QTimer* timerPower;
    QString obje;                           //String para leer los datos del archivo
    QString obs;
    bool sound = true;
};

#endif // MAINWINDOW_H
