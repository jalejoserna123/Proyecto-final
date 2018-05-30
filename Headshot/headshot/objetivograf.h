#ifndef OBJETIVOGRAF_H
#define OBJETIVOGRAF_H

#include "objetivo.h"
#include <QPainter>
#include <qbrush.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

class objetivoGraf: public QGraphicsItem //Clase de objetivos (cabezas) para graficar
{
public:
    objetivoGraf(float px_, float py_, float height_, float widht_, QString direccion_);
    ~objetivoGraf();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    objetivo* getObjetivo();
private:
    objetivo* objetivos;
    float escala;
};

#endif // OBJETIVOGRAF_H

