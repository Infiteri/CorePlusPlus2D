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
        view = Matrix4::Translate(&position);
        
    }

    void Camera::CalculateProjection()
    {
    }
}