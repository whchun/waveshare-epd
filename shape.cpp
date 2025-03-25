/**
 * @file shape.cpp
 * @brief Basic drawing, text, and image related (coordinate).
 *
 * More reference is in display wiki page
 * https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module
 *
 * @author whchun
 * @date 2025-03-24
 */
#include "shape.h"

int Point::getBytesSize()
{
    // Each is short, or double bytes
    return (2 * sizeof(uint8_t)) + (2 * sizeof(uint8_t));
}

uint8_t *Point::getBytes()
{
    int bytesSize = getBytesSize();
    uint8_t *bytes = new uint8_t[bytesSize];

    bytes[0] = (_x >> 8) & 0xFF;
    bytes[1] = _x & 0xFF;
    bytes[2] = (_y >> 8) & 0xFF;
    bytes[3] = _y & 0xFF;

    return bytes;
}

int Line::getBytesSize()
{
    return _p1.getBytesSize() + _p2.getBytesSize();
}

uint8_t *Line::getBytes()
{
    int bytesSize = getBytesSize();
    uint8_t *bytes = new uint8_t[bytesSize];

    int currentBytesSize = _p1.getBytesSize() * sizeof(uint8_t);
    memcpy(bytes, _p1.getBytes(), currentBytesSize);
    memcpy(bytes + currentBytesSize, _p2.getBytes(), _p2.getBytesSize() * sizeof(uint8_t));

    return bytes;
}

int Rectangle::getBytesSize()
{
    return _p1.getBytesSize() + _p2.getBytesSize();
}

uint8_t *Rectangle::getBytes()
{
    int bytesSize = getBytesSize();
    uint8_t *bytes = new uint8_t[bytesSize];

    int currentBytesSize = _p1.getBytesSize() * sizeof(uint8_t);
    memcpy(bytes, _p1.getBytes(), currentBytesSize);
    memcpy(bytes + currentBytesSize, _p2.getBytes(), _p2.getBytesSize() * sizeof(uint8_t));

    return bytes;
}

int Circle::getBytesSize()
{
    return _p1.getBytesSize() + getRadiusBytesSize();
}

uint8_t *Circle::getBytes()
{
    int bytesSize = getBytesSize();
    uint8_t *bytes = new uint8_t[bytesSize];

    int currentBytesSize = _p1.getBytesSize() * sizeof(uint8_t);
    memcpy(bytes, _p1.getBytes(), currentBytesSize);
    memcpy(bytes + currentBytesSize, getRadiusBytes(), getRadiusBytesSize());

    return bytes;
}

int Circle::getRadiusBytesSize()
{
    return 2 * sizeof(uint8_t); // Return short or double bytes
}

uint8_t *Circle::getRadiusBytes()
{
    int bytesSize = getRadiusBytesSize();
    uint8_t *bytes = new uint8_t[bytesSize];
    bytes[0] = (_radius >> 8) & 0xFF;
    bytes[1] = _radius & 0xFF;

    return bytes;
}

int Triangle::getBytesSize()
{
    return _p1.getBytesSize() + _p2.getBytesSize() + _p3.getBytesSize();
}

uint8_t *Triangle::getBytes()
{
    int bytesSize = getBytesSize();
    uint8_t *bytes = new uint8_t[bytesSize];

    int currentBytesSize = _p1.getBytesSize() * sizeof(uint8_t);
    memcpy(bytes, _p1.getBytes(), currentBytesSize);
    memcpy(bytes + currentBytesSize, _p2.getBytes(), _p2.getBytesSize() * sizeof(uint8_t));
    currentBytesSize += (_p2.getBytesSize() * sizeof(uint8_t));
    memcpy(bytes + currentBytesSize, _p3.getBytes(), _p3.getBytesSize() * sizeof(uint8_t));

    return bytes;
}