#ifndef PROYECTOR_H
#define PROYECTOR_H

#include <QPainter>
#include <qbrush.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

class proyector           //Clase del cañon
{
private:
    float px;
    float py;
    float delta;
public:
    proyector(float px_=0, float py_=0);
    float get_px() const;
    float get_py() const;
    void set_delta(float delta_);
};

#endif // PROYECTOR_H

