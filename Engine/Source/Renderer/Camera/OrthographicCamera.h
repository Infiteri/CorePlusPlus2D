#pragma once

#include "Base.h"
#include "Camera.h"

namespace Core
{
    class CE_API OrthographicCamera : public Camera
    {

    public:
        enum OriginPoint
        {
            Left,
            Middle
        };

    private:
        float width;
        float height;

        OriginPoint originPoint;

    public:
        OrthographicCamera(float width, float height);
        ~OrthographicCamera();

        void CalculateProjection(float width, float height);

        void SetOriginPoint(OriginPoint point);
        inline OriginPoint GetOriginPoint() { return originPoint; };
    };
}