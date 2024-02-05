#include "Vectors.h"

namespace Core
{
    Vector2::Vector2()
    {
        Set(0, 0);
    }

    Vector2::Vector2(float x, float y)
    {
        Set(x, y);
    }

    Vector2::Vector2(const Vector2 &v2)
    {
        Set(v2.x, v2.y);
    }

    Vector2::~Vector2()
    {
    }

    void Vector2::Set(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
}