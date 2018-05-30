#include "proyectilgraf.h"

proyectilGraf::proyectilGraf(float px_, float py_, float V, float delta_): escala(1)
{
    proyectiles = new proyectil(px_, py_, V, delta_);
    setPos(proyectiles->getX()*escala, (500-proyectiles->getY())*escala);
}

proyectilGraf::proyectilGraf(float px_, float py_, float vx_, float vy_, float ax_, float ay_):escala(1)
{
    proyectiles = new proyectil(px_,py_,vx_,vy_,ax_,ay_);
    setPos(proyectiles->getX()*escala, (500-proyectiles->getY())*escala);
}

proyectilGraf::~proyectilGraf()
{
    delete proyectiles;
}

QRectF proyectilGraf::boundingRect() const
{
        return QRectF(-1*proyectiles->getR(),-1*proyectiles->getR(),2*proyectiles->getR(),2*proyectiles->getR());
}

void proyectilGraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());
}

proyectil *proyectilGraf::getProyectil()
{
    return proyectiles;
}

void proyectilGraf::actualizar(float dt, float v_lim)
{
    proyectiles->actualizar(dt);
    setPos(proyectiles->getX()*escala, (v_lim-proyectiles->getY())*escala);
}
