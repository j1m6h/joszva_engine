#ifndef VECTOR2_H
#define VECTOR2_H

namespace joszva::graphics
{
    template<typename T>
    class vector2
    {
    public:
        vector2(T x, T y) : x(x), y(y) {}

        T x;
        T y;
    };
}
#endif