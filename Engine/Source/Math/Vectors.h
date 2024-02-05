#pragma once

#include "Base.h"

namespace Core
{
    class CE_API Vector2
    {
    public:
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);
        Vector2(const Vector2 &v2);
        ~Vector2();

        void Set(float x, float y);
    };
}