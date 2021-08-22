#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#include "config.h"

namespace joszva::graphics
{
    class color
    {
    public:
        color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
        ~color();

        static const color black;
        static const color white;

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
}
#endif