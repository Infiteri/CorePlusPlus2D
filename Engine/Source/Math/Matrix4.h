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

        static Matrix4 Multiply(Matrix4 *a, Matrix4 *b);
        static Matrix4 Multiply(Matrix4 a, Matrix4 b);

        static Matrix4 RotationXYZ(Vector3 vec);
        static Matrix4 RotationXYZ(Vector3 *vec);
        static Matrix4 RotationXYZ(float rotationX, float rotationY, float rotationZ);

        static Matrix4 RotationZYX(Vector3 vec);
        static Matrix4 RotationZYX(Vector3 *vec);
        static Matrix4 RotationZYX(float rotationX, float rotationY, float rotationZ);

        static Matrix4 RotationX(float rotation);
        static Matrix4 RotationY(float rotation);
        static Matrix4 RotationZ(float rotation);

        static Matrix4 Translate(Vector3 *v2);
        static Matrix4 Translate(const Vector3 &v2);

        static Matrix4 Invert(Matrix4 *a);

        static Matrix4 Ortho(float left, float right, float top, float bottom, float n, float f);

        static Matrix4 Scale(Vector3 *vec);
        static Matrix4 Scale(float x, float y, float z);
    };
}