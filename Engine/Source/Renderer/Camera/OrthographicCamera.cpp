#include "OrthographicCamera.h"

namespace Core
{
    OrthographicCamera::OrthographicCamera(float width, float height)
    {
        originPoint = Left;
        CalculateView();
        CalculateProjection(width, height);
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::CalculateProjection(float _width, float _height)
    {
        this->width = _width;
        this->height = _height;

        switch (originPoint)
        {
        case Middle:
            projection = Matrix4::Ortho(-(width / 2), width / 2, -(height / 2), height / 2, -1.0, 1.0);
            break;

        case Left:
        default:
            projection = Matrix4::Ortho(0, width, 0, height, -1.0, 1.0);
            break;
        }
    }

    void OrthographicCamera::SetOriginPoint(OriginPoint point)
    {
        if (originPoint == point)
            return;

        originPoint = point;
        CalculateProjection(width, height);
    }
}