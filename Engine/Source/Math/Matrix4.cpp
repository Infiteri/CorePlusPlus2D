#include "Matrix4.h"

namespace Core
{
    Matrix4::Matrix4()
    {
        for (int i = 0; i < 16; i++)
        {
            data[i] = 0;
        }

        data[0] = data[5] = data[10] = data[15] = 1.0f;
    }

    Matrix4::~Matrix4()
    {
    }

    Matrix4 Matrix4::TranslateVec2(Vector2 *v2)
    {
        Matrix4 m;
        m.data[12] = v2->x;
        m.data[13] = v2->y;
        return m;
    }

    Matrix4 Matrix4::TranslateVec2(const Vector2 &v2)
    {
        Matrix4 m;
        m.data[12] = v2.x;
        m.data[13] = v2.y;
        return m;
    }

    Matrix4 Matrix4::Translate(Vector3 *v2)
    {
        Matrix4 m;
        m.data[12] = v2->x;
        m.data[13] = v2->y;
        m.data[14] = v2->z;
        return m;
    }

    Matrix4 Matrix4::Translate(const Vector3 &v2)
    {
        Matrix4 m;
        m.data[12] = v2.x;
        m.data[13] = v2.y;
        m.data[14] = v2.z;
        return m;
    }

    Matrix4 Matrix4::Invert(Matrix4 *a)
    {
        Matrix4 m;

        float a00 = a->data[0];
        float a01 = a->data[1];
        float a02 = a->data[2];
        float a03 = a->data[3];
        float a10 = a->data[4];
        float a11 = a->data[5];
        float a12 = a->data[6];
        float a13 = a->data[7];
        float a20 = a->data[8];
        float a21 = a->data[9];
        float a22 = a->data[10];
        float a23 = a->data[11];
        float a30 = a->data[12];
        float a31 = a->data[13];
        float a32 = a->data[14];
        float a33 = a->data[15];
        float b00 = a00 * a11 - a01 * a10;
        float b01 = a00 * a12 - a02 * a10;
        float b02 = a00 * a13 - a03 * a10;
        float b03 = a01 * a12 - a02 * a11;
        float b04 = a01 * a13 - a03 * a11;
        float b05 = a02 * a13 - a03 * a12;
        float b06 = a20 * a31 - a21 * a30;
        float b07 = a20 * a32 - a22 * a30;
        float b08 = a20 * a33 - a23 * a30;
        float b09 = a21 * a32 - a22 * a31;
        float b10 = a21 * a33 - a23 * a31;
        float b11 = a22 * a33 - a23 * a32;
        // Calculate the determinant
        float det =
            b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

        det = 1.0 / det;

        m.data[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
        m.data[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
        m.data[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
        m.data[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
        m.data[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
        m.data[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
        m.data[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
        m.data[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
        m.data[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
        m.data[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
        m.data[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
        m.data[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
        m.data[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
        m.data[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
        m.data[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
        m.data[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;

        return m;
    }

    Matrix4 Matrix4::Ortho(float left, float right, float top, float bottom, float n, float f)
    {
        Matrix4 m;

        float lr = 1.0 / (left - right);
        float bt = 1.0 / (bottom - top);
        float nf = 1.0 / (f - n);

        m.data[0] = -2.0 * lr;
        m.data[5] = -2.0 * bt;
        m.data[10] = 2.0 * nf;

        m.data[12] = (left + right) * lr;
        m.data[13] = (top + bottom) * bt;
        m.data[14] = (f + n) * nf;

        return m;
    }
}