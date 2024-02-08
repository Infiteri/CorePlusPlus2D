#pragma once

#include "Base.h"
#include "Math/Matrix4.h"
#include "Math/Vectors.h"

namespace Core
{
    struct CE_API Transform
    {
        Vector3 Position;
        // float Rotation;
        // Vector2 Scale;

        Matrix4 GetTransformMatrix();
    };
}