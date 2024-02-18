#include "CameraSystem.h"
#include "Core/Logger.h"

namespace Core
{

    static std::unordered_map<std::string, OrthographicCamera *> ortho_cameras;
    static OrthographicCamera *active_camera; // TODO: change once this is perspective
    static std::string active_camera_name;

    void CameraSystem::Init()
    {
        CE_DEFINE_LOG_CATEGORY("Camera System", "CAM_SYS");
    }

    void CameraSystem::Shutdown()
    {
        auto it = ortho_cameras.begin();
        while (it != ortho_cameras.end())
        {
            delete it->second;
            ortho_cameras[it->first] = nullptr;
            it++;
        }
    }

    void CameraSystem::CreateOrthoCamera(float width, float height, const std::string &name)
    {
        OrthographicCamera *c = new OrthographicCamera(width, height);
        ortho_cameras[name] = c;

        CE_LOG("CAM_SYS", Debug, "Registered camera: %s.", name.c_str());
    }

    void CameraSystem::Activate(const std::string &name)
    {
        if (!ortho_cameras[name])
        {
            CE_LOG("CAM_SYS", Error, "Cannot activate camera: %s. (NOT EXISTENT)", name.c_str());
            return;
        }

        active_camera = ortho_cameras[name];
        active_camera_name = name;
        CE_LOG("CAM_SYS", Debug, "Activated camera: %s.", name.c_str());
    }

    void CameraSystem::EraseCamera(const std::string &name)
    {
        ortho_cameras.erase(name);
    }

    void CameraSystem::AddOrthographicCamera(OrthographicCamera *camera, const std::string &name)
    {
        ortho_cameras[name] = camera;
    }

    OrthographicCamera *CameraSystem::GetActiveAsOrtho()
    {
        return (OrthographicCamera *)active_camera;
    }

    void CameraSystem::UpdateActiveCamera()
    {
        if (active_camera)
        {
            active_camera->CalculateView();
        }
    }

    std::string CameraSystem::GetActiveCameraName()
    {
        return active_camera_name;
    }
}