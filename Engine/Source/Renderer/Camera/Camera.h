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
        float zoom;
        Vector3 position;

    public:
        Camera();
        ~Camera();

        void CalculateView();
        virtual void CalculateProjection();

        virtual void AddZoom(float newZoom);
        virtual void SetZoom(float newZoom);
        inline float GetZoom() { return zoom; };

        inline Matrix4 *GetProjection() { return &projection; };
        inline Matrix4 *GetView() { return &view; };
        inline Matrix4 GetViewInverted() { return Matrix4::Invert(&view); };
        inline Vector3 *GetPosition() { return &position; };
    };
}