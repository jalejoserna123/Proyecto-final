#include "obstaculograf.h"

obstaculoGraf::obstaculoGraf(float px_, float py_, float height_, float widht_, QString direccion_): escala(1)
{
    obstaculos = new obstaculo(px_,py_,height_,widht_,direccion_);
    setPos(obstaculos->getX(),500-obstaculos->getY());
}

obstaculoGraf::~obstaculoGraf()
{
    delete obstaculos;
}

QRectF obstaculoGraf::boundingRect() const
{
    return QRectF(-1*obstaculos->getW()/2,-1*obstaculos->getH()/2,obstaculos->getW(),obstaculos->getH());

}

void obstaculoGraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-1*obstaculos->getW()/2,-1*obstaculos->getH()/2,obstaculos->getW(),obstaculos->getH(),QPixmap(obstaculos->getDir()));
    setPos(obstaculos->getX(),500-obstaculos->getY());

}

obstaculo *obstaculoGraf::getObstaculo()
{
    return obstaculos;
}


