#pragma once

#include "Base.h"
#include "Camera.h"

namespace Core
{
    class CE_API OrthographicCamera : public Camera
    {
    private:
        float width;
        float height;

    public:
        OrthographicCamera(float width, float height);
        ~OrthographicCamera();

        void CalculateProjection(float width, float height);
    };
}