#include "shape.h"

int Coordinate::getBytesSize()
{
    // 2 bytes for x and y
    return 4;
}

uint8_t *Coordinate::getBytes()
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
    return NULL;
}