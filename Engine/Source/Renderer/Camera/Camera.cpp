#include "Camera.h"

namespace Core
{
    Camera::Camera()
    {
    }

    Camera::~Camera()
    {
    }

    void Camera::CalculateView()
    {
        view = Matrix4::TranslateVec2(&position);
    }

    void Camera::CalculateProjection()
    {
    }
}