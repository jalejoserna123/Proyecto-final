#ifndef OBSTACULO_H
#define OBSTACULO_H


#include <QString>

class obstaculo     //Clase de obstaculos
{
private:
    float px;
    float py;
    float height;
    float widht;
    QString direccion;
public:
    obstaculo(float px_, float py_, float height_, float widht_, QString direccion_);
    float getX() const;
    float getY() const;
    float getH() const;
    float getW() const;
    QString getDir() const;
};

#endif // OBSTACULO_H
