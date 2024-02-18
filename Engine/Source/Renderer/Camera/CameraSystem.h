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

        /// @brief Erases a camera from the set, not the same as deleting it, assuming the name is on the names passed in when adding the AddOrthographicCamera call. (IN SHORT DELETES THE CAMERA FROM COLLECTION BUT DOESN'T CLEAR THE POINTED TO MEMORY)
        /// @param name Camera name
        static void EraseCamera(const std::string& name);

        static void AddOrthographicCamera(OrthographicCamera* camera, const std::string& name);

        /// @brief Supposedly the active camera is orthographic.
        /// @return A pointer to an orthographic camera
        static OrthographicCamera *GetActiveAsOrtho();

        /// @brief Will update its view matrix. Projection is handled by the renderer.
        static void UpdateActiveCamera();

        static std::string GetActiveCameraName();
    };
} // namespace Core
