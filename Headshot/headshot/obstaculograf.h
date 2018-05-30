#ifndef OBSTACULOGRAF_H
#define OBSTACULOGRAF_H
#define P "C:/Users/PERSONAL/Pictures/cadena.png"
#define S "C:/Users/PERSONAL/Pictures/Bloque_Ladrillo.png"

#include "obstaculo.h"
#include <QPainter>
#include <qbrush.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

class obstaculoGraf: public QGraphicsItem //Clase de obstaculos (Para graficar)
{
public:
    obstaculoGraf(float px_, float py_, float height_, float widht_, QString direccion_);
    ~obstaculoGraf();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    obstaculo* getObstaculo();
private:
    obstaculo* obstaculos;
    float escala;
};

#endif // OBSTACULOGRAF_H
