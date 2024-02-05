#pragma once

#include "Base.h"
#include "Vectors.h"

namespace Core
{
    class CE_API Matrix4
    {
    public:
        float data[16];

        Matrix4();
        ~Matrix4();

        static Matrix4 TranslateVec2(Vector2 *v2);
        static Matrix4 TranslateVec2(const Vector2 &v2);

        static Matrix4 Invert(Matrix4* a);

        static Matrix4 Ortho(float left, float right, float top, float bottom, float n, float f);
    };
}