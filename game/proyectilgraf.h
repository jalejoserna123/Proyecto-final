#ifndef PROYECTILGRAF_H
#define PROYECTILGRAF_H

#include "proyectil.h"
#include <QPainter>
#include <qbrush.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

class proyectilGraf: public QGraphicsItem
{
public:
    proyectilGraf(float px_, float py_, float V, float delta_);
    proyectilGraf(float px_, float py_, float vx_, float vy_, float ax_, float ay_);
    ~proyectilGraf();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    proyectil* getProyectil();
    void actualizar(float dt, float v_lim);
private:
    proyectil* proyectiles;
    float escala;
};

#endif // PROYECTILGRAF_H
