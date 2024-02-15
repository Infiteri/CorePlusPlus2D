#pragma once

#include "Base.h"
#include "Math/Matrix4.h"
#include "Math/Vectors.h"

namespace Core
{
    struct CE_API Transform
    {
        Vector3 Position;          /// @brief Transform position. Vector3D
        Vector3 Rotation{0, 0, 0}; /// @brief Transform rotation. Vector3D
        Vector3 Scale{1, 1, 1};    /// @brief Transform scale. Vector3D

        Matrix4 GetTransformMatrix();
    };
}