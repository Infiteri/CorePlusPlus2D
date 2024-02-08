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

    Vector3::Vector3()
    {
        Set(0, 0, 0);
    }

    Vector3::Vector3(float x, float y, float z)
    {
        Set(x, y, z);
    }

    Vector3::Vector3(const Vector3 &v2)
    {
        Set(v2.x, v2.y, v2.z);
    }

    Vector3::~Vector3()
    {
    }

    void Vector3::Set(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector4::Vector4()
    {
        Set(0, 0, 0, 0);
    }

    Vector4::Vector4(float x, float y, float z, float w)
    {
        Set(x, y, z, w);
    }

    Vector4::Vector4(const Vector4 &v2)
    {
        Set(v2.x, v2.y, v2.z, v2.w);
    }

    Vector4::~Vector4()
    {
    }

    void Vector4::Set(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
}