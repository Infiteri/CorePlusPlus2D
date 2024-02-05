#include "OrthographicCamera.h"

namespace Core
{
    OrthographicCamera::OrthographicCamera(float width, float height)
    {
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

        projection = Matrix4::Ortho(0, width * 2, 0, height * 2, -1.0, 1.0);
    }
}