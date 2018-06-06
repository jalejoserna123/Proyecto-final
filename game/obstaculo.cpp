#include "obstaculo.h"


obstaculo::obstaculo(float px_, float py_, float height_, float widht_, QString direccion_):px(px_), py(py_), height(height_), widht(widht_), direccion(direccion_)
{

}

float obstaculo::getX() const
{
    return px;
}

float obstaculo::getY() const
{
    return py;
}

float obstaculo::getH() const
{
    return height;
}

float obstaculo::getW() const
{
    return widht;
}

QString obstaculo::getDir() const
{
    return direccion;
}


