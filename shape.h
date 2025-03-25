#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"
#include <Arduino.h>

class Coordinate
{
public:
    Coordinate(int x, int y) : _x(x), _y(y) {};

    int getBytesSize();
    uint8_t *getBytes();

private:
    int _x;
    int _y;
};

class Shape
{
public:
    virtual int getBytesSize() = 0;
    virtual uint8_t *getBytes() = 0;
};

class Line : public Shape
{
public:
    Line(Coordinate p1, Coordinate p2) : _p1(p1), _p2(p2) {};

    int getBytesSize();
    uint8_t *getBytes();

private:
    Coordinate _p1;
    Coordinate _p2;
};

#endif