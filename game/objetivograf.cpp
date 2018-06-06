#include "objetivograf.h"

objetivoGraf::objetivoGraf(float px_, float py_, float height_, float widht_, QString direccion_): escala(1)
{
    objetivos = new objetivo(px_,py_,height_,widht_,direccion_);
    setPos(objetivos->getX()*escala, (500-objetivos->getY())*escala);
}

objetivoGraf::~objetivoGraf()
{
    delete objetivos;
}

QRectF objetivoGraf::boundingRect() const
{
    return QRectF(-1*objetivos->getW()/2,-1*objetivos->getH()/2,objetivos->getW(),objetivos->getH());
}

void objetivoGraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setBrush(Qt::black);
    //painter->drawEllipse(boundingRect());
    painter->drawPixmap(-1*objetivos->getW()/2,-1*objetivos->getH()/2,2*objetivos->getW()/2,2*objetivos->getH()/2, QPixmap(objetivos->getDir()));
    setPos(objetivos->getX()*escala, (500-objetivos->getY())*escala);
}

objetivo *objetivoGraf::getObjetivo()
{
    return objetivos;
}


