/**
 * @file shape.h
 * @brief Basic drawing, text, and image related (coordinate).
 *
 * More reference is in display wiki page
 * https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module
 *
 * @author whchun
 * @date 2025-03-24
 */
#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"
#include <Arduino.h>

class Point
{
public:
    Point(int x, int y) : _x(x), _y(y) {};

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
    Line(Point p1, Point p2) : _p1(p1), _p2(p2) {};

    int getBytesSize();
    uint8_t *getBytes();

private:
    Point _p1;
    Point _p2;
};

class Rectangle : public Shape
{
public:
    Rectangle(Point p1, Point p2) : _p1(p1), _p2(p2) {};

    int getBytesSize();
    uint8_t *getBytes();

private:
    Point _p1;
    Point _p2;
};

class Circle : public Shape
{
public:
    Circle(Point p1, int radius) : _p1(p1), _radius(radius) {};

    int getBytesSize();
    uint8_t *getBytes();

private:
    Point _p1;
    int _radius;

    int getRadiusBytesSize();
    uint8_t *getRadiusBytes();
};

class Triangle : public Shape
{
public:
    Triangle(Point p1, Point p2, Point p3) : _p1(p1), _p2(p2), _p3(p3) {};

    int getBytesSize();
    uint8_t *getBytes();

private:
    Point _p1;
    Point _p2;
    Point _p3;
};

#endif