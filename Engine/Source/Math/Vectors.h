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

        class CE_API Vector3
    {
    public:
        float x;
        float y;
        float z;

        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector3 &v2);
        ~Vector3();

        void Set(float x, float y, float z);
        void Set(Vector3* v);
    };

    class CE_API Vector4
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Vector4();
        Vector4(float x, float y, float z, float w);
        Vector4(const Vector4 &v2);
        ~Vector4();

        void Set(float x, float y, float z, float w);
    };
}