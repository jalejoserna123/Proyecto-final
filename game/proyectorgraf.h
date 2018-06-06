#ifndef PROYECTORGRAF_H
#define PROYECTORGRAF_H

#include "proyector.h"
#include <QPainter>
#include <qbrush.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

class proyectorGraf: public QGraphicsItem
{
public:
    proyectorGraf(float px_, float py_);
    ~proyectorGraf();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    proyector *getProyector();
private:
    proyector* proyect;
};

#endif // PROYECTORGRAF_H
