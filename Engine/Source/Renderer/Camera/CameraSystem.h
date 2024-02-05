#pragma once

#include "Base.h"
#include "Camera.h"
#include <string>
#include <unordered_map>
#include "OrthographicCamera.h"

namespace Core
{
    class CE_API CameraSystem
    {
    public:
        CameraSystem(){};
        ~CameraSystem(){};

        static void Init();
        static void Shutdown();

        static void CreateOrthoCamera(float width, float height, const std::string &name);
        static void Activate(const std::string &name);

        /// @brief Supposedly the active camera is orthographic.
        /// @return A pointer to an orthographic camera
        static OrthographicCamera *GetActiveAsOrtho();

        /// @brief Will update its view matrix. Projection is handled by the renderer.
        static void UpdateActiveCamera();

        static std::string GetActiveCameraName();
    };
} // namespace Core
