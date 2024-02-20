#include "OrthographicCamera.h"
#include "Core/Logger.h"

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

        CE_TRACE("Zoom: %.3f", zoom);

        switch (originPoint)
        {
        case Middle:
            projection = Matrix4::Ortho(-(width / (2 * zoom)), width / (2 * zoom), -(height / (2 * zoom)), height / (2 * zoom), -1.0, 1.0);
            break;

        case Left:
        default:
            projection = Matrix4::Ortho(0, width * zoom, 0, height * zoom, -1.0, 1.0);
            break;
        }
    }

    void OrthographicCamera::CalculateProjection()
    {
        CalculateProjection(width, height);
    }

    void OrthographicCamera::AddZoom(float newZoom)
    {
        zoom += newZoom;
        CalculateProjection(width, height);
    }

    void OrthographicCamera::SetZoom(float newZoom)
    {
        zoom = newZoom;
        CalculateProjection(width, height);
    }

    void OrthographicCamera::SetOriginPoint(OriginPoint point)
    {
        if (originPoint == point)
            return;

        originPoint = point;
        CalculateProjection(width, height);
    }
}