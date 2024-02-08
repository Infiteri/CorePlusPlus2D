#pragma once

#include "Base.h"

namespace Core
{
    class CE_API Color
    {
    public:
        float r;
        float g;
        float b;
        float a;

        Color();
        Color(float r, float g, float b, float a);
        Color(const Color& color);
        ~Color();

        void Set(float r, float g, float b, float a);
    };
}