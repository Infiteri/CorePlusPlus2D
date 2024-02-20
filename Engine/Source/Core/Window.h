#pragma once

#include "Base.h"

class GLFWwindow;

namespace Core
{
    enum class WindowSizeMode
    {
        Normal,     /// @brief Normal type window, x, y, width and height are respected.
        FullScreen, /// @brief Fully fullscreen with no top bar
        Maximized,  /// @brief Fully fullscreen with  top bar
    };

    struct WindowInformation
    {
        int x;
        int y;
        int width;
        int height;
        const char *title;
        bool VSync;

        bool acceptDefaultWindowResizeCallback;
        WindowSizeMode mode;
    };

    class CE_API Window
    {

    private:
        WindowInformation info;
        GLFWwindow *handle;

        int x;
        int y;
        int width;
        int height;

    public:
        Window(const WindowInformation &information);
        ~Window();

        bool ShouldRun();
        void Update();

        int GetWidth();
        int GetHeight();

        int GetX();
        int GetY();

        inline WindowInformation *GetInformation() { return &info; };
        inline GLFWwindow *GetHandle() { return handle; };
    };
}