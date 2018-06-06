#ifndef PROYECTIL_H
#define PROYECTIL_H
#define PI 3.141592654

#include <time.h>
#include <QPainter>
#include <qbrush.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <math.h>

class proyectil
{
private:
    float radio= 6;
    float px;
    float py;
    float vx;
    float vy;
    float ax;
    float ay;
    float masa =  50;                     //masa
    float e = -0.4;
    float k = 0.0001570796326795;
public:
    proyectil(float px_, float py_, float V, float delta);
    proyectil(float px_, float py_, float vx_, float vy_, float ax_, float ay_);
    ~proyectil();
    void setVel(float x, float y);          //metodo para asignar la velocidad (en X y en Y)
    void setPoint(float x, float y);        //metodo para asignar la posicion (en X y en Y)
    void actualizar(float dt);              //metodo que cambia los valores de posicion (realiza el movimiento), recibe el lapso de tiempo transcurrido
    float getX() const;                  //metodos para retornar los atributos
    float getY() const;
    float getR() const;
    float getVx() const;
    float getVy() const;
    float getAx() const;
    float getAy() const;
    float get_e() const;
};

#endif // PROYECTIL_H
