#include "proyectorgraf.h"

proyectorGraf::proyectorGraf(float px_, float py_)
{
    proyect = new proyector(px_, py_);
    setPos(proyect->get_px(), 500-proyect->get_py());
}

proyectorGraf::~proyectorGraf()
{
    delete proyect;
}


QRectF proyectorGraf::boundingRect() const
{
        return QRectF(-1*70,-1*50,2*70,2*50);
}

void proyectorGraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-1*70,-1*50,2*70,2*50,QPixmap(":/Img/canon"));
    setPos(proyect->get_px(), 500-proyect->get_py());
}

proyector *proyectorGraf::getProyector()
{
    return proyect;
}


