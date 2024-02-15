#pragma once

#include "Test.h"

class CameraSystemTest : public Core::Test
{
public:
    CameraSystemTest() : Test("Camera System Test"){};
    ~CameraSystemTest(){};

    bool Run()
    {
        Core::CameraSystem::CreateOrthoCamera(1024, 576, "TEST_CAMERA");
        Core::CameraSystem::Activate("TEST_CAMERA");

        return Core::CameraSystem::GetActiveAsOrtho() != nullptr;
    };
};
