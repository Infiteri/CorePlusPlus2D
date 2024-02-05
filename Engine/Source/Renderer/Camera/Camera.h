#pragma once

#include "Base.h"
#include "Math/Matrix4.h"
#include "Math/Vectors.h"

namespace Core
{
    class CE_API Camera
    {
    protected:
        Matrix4 projection;
        Matrix4 view;

        Vector2 position;

    public:
        Camera();
        ~Camera();

        void CalculateView();
        virtual void CalculateProjection();

        inline Matrix4 *GetProjection() { return &projection; };
        inline Matrix4 *GetView() { return &view; };
        inline Matrix4 GetViewInverted() { return Matrix4::Invert(&view); };
        inline Vector2 *GetPosition() { return &position; };
    };
}