#ifndef OBJETIVO_H
#define OBJETIVO_H

#include <QString>

class objetivo
{
private:
    float height;
    float widht;
    float px;
    float py;
    QString direccion;
public:
    objetivo(float px_, float py_, float height_, float widht_, QString direccion_);
    float getX() const;
    float getY() const;
    float getH() const;
    float getW() const;
    QString getDir() const;
};

#endif // OBJETIVO_H
