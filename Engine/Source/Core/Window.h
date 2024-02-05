#pragma once

#include "Base.h"
#include "GLFW/glfw3.h"

namespace Core
{
    struct WindowInformation
    {
        int x;
        int y;
        int width;
        int height;
        const char *title;
    };

    class CE_API Window
    {
    public:
    private:
        WindowInformation info;
        GLFWwindow *handle;

        int width;
        int height;

    public:
        Window(const WindowInformation &information);
        ~Window();

        bool ShouldRun();
        void Update();

        int GetWidth();
        int GetHeight();

        inline WindowInformation *GetInformation() { return &info; };
        inline GLFWwindow *GetHandle() { return handle; };
    };
}