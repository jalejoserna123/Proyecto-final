#include "proyectil.h"

proyectil::proyectil(float px_, float py_, float V, float delta): px(px_), py(py_)
{
    vx = V*cos(delta*PI/180);
    vy = V*sin(delta*PI/180);
    //k = 0.1*0.001*PI/2.0;
}

proyectil::proyectil(float px_, float py_, float vx_, float vy_, float ax_, float ay_):px(px_), py(py_), vx(vx_), vy(vy_), ax(ax_), ay(ay_)
{

}

proyectil::~proyectil()
{

}

void proyectil::setVel(float x_, float y_)
{
    vx = x_;
    vy = y_;
}

void proyectil::setPoint(float x_, float y_)
{
    px = x_;
    py = y_;
}

void proyectil::actualizar(float dt)
{
    float v = sqrt(pow(vx,2)+pow(vy,2));
    float theta = atan2(vy,vx);
    ax = -1*(k*v*v*radio*radio*cos(theta))/masa;
    ay = (-1*(k*v*v*radio*radio*sin(theta))/masa) - 10;
    //ax = 0;
    //ay = -10;
    px+=vx*dt + dt*dt*ax/2;
    py+=vy*dt + dt*dt*ay/2;
    vx+=ax*dt;
    vy+=ay*dt;
}

float proyectil::getX() const
{
    return px;
}

float proyectil::getY() const
{
    return py;
}

float proyectil::getR() const
{
    return radio;
}

float proyectil::getVx() const
{
    return vx;
}

float proyectil::getVy() const
{
    return vy;
}

float proyectil::getAx() const
{
    return ax;
}

float proyectil::getAy() const
{
    return ay;
}

float proyectil::get_e() const
{
    return e;
}
