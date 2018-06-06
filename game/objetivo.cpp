#include "objetivo.h"

objetivo::objetivo(float px_, float py_, float height_, float widht_, QString direccion_):px(px_), py(py_), height(height_), widht(widht_), direccion(direccion_)
{

}

float objetivo::getX() const
{
    return px;
}

float objetivo::getY() const
{
    return py;
}

float objetivo::getH() const
{
    return height;
}

float objetivo::getW() const
{
    return widht;
}

QString objetivo::getDir() const
{
    return direccion;
}
