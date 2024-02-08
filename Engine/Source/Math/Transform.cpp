#include "Transform.h"

namespace Core
{
    Matrix4 Transform::GetTransformMatrix()
    {
        return Matrix4::Translate(Position);
    }
}