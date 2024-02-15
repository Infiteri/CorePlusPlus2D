#include "Transform.h"

namespace Core
{
    Matrix4 Transform::GetTransformMatrix()
    {
        Matrix4 translation = Matrix4::Translate(&Position);
        Matrix4 rotated = Matrix4::RotationZYX(&Rotation);
        Matrix4 scaled = Matrix4::Scale(&Scale);

        return Matrix4::Multiply(Matrix4::Multiply(translation, rotated), scaled);
    }
}