#include "Camera.h"

namespace Core
{
    Camera::Camera()
    {
        zoom = 1.0f;
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

    void Camera::AddZoom(float newZoom)
    {
        zoom += newZoom;
    }

    void Camera::SetZoom(float newZoom)
    {
        zoom = newZoom;
    }
}