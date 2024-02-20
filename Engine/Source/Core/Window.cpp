#include "Window.h"
#include "Core/Logger.h"
#include "Renderer/Renderer.h"
#include "GLFW/glfw3.h"

#include "Input.h"

namespace Core
{
    double accumulatedScrollX = 0.0;
    double accumulatedScrollY = 0.0;

    void WINDOW_INTERNAL_Key(GLFWwindow *handle, int key, int scancode, int action, int mods);
    void WINDOW_INTERNAL_Button(GLFWwindow *handle, int key, int action, int mods);
    void WINDOW_INTERNAL_Mouse(GLFWwindow *handle, double x, double y);
    void WINDOW_INTERNAL_Resize(GLFWwindow *handle, int w, int h);
    void WINDOW_INTERNAL_Scroll(GLFWwindow *handle, double x, double y);

    Window::Window(const WindowInformation &information)
    {
        info.x = information.x;
        info.y = information.y;
        info.width = information.width;
        info.height = information.height;
        info.title = information.title;
        info.mode = information.mode;
        info.VSync = information.VSync;
        info.acceptDefaultWindowResizeCallback = information.acceptDefaultWindowResizeCallback; // ! Will prolly not work.

        glfwInit();

        GLFWmonitor *monitor = nullptr;
        if (info.mode == WindowSizeMode::FullScreen)
            monitor = glfwGetPrimaryMonitor();

        handle = glfwCreateWindow(info.width, info.height, info.title, monitor, NULL);

        switch (info.mode)
        {
        case WindowSizeMode::Maximized:
            glfwMaximizeWindow(handle);
            break;
        }

        glfwMakeContextCurrent(handle);

        //? callbacks
        {
            glfwSetKeyCallback(handle, WINDOW_INTERNAL_Key);
            glfwSetMouseButtonCallback(handle, WINDOW_INTERNAL_Button);
            glfwSetCursorPosCallback(handle, WINDOW_INTERNAL_Mouse);
            glfwSetScrollCallback(handle, WINDOW_INTERNAL_Scroll);

            if (info.acceptDefaultWindowResizeCallback)
                glfwSetWindowSizeCallback(handle, WINDOW_INTERNAL_Resize);
        }

        glfwGetWindowSize(handle, &width, &height);
        Renderer::ResizeViewport({width, height});

        if (info.VSync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    Window::~Window()
    {
        glfwDestroyWindow(handle);
        glfwTerminate();
    }

    bool Window::ShouldRun()
    {
        return !glfwWindowShouldClose(handle);
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(handle);

        {
            double dx, dy;
            glfwGetCursorPos(handle, &dx, &dy);
            INPUT_INTERNAL_UpdateMouse((float)dx, (float)dy);
        }

        INPUT_INTERNAL_UpdateScroll(accumulatedScrollX, accumulatedScrollY);
        accumulatedScrollX = accumulatedScrollY = 0;

        glfwGetWindowPos(handle, &x, &y);
        glfwGetWindowSize(handle, &width, &height);
    }

    int Window::GetWidth()
    {
        return width;
    }

    int Window::GetHeight()
    {
        return height;
    }

    int Window::GetX()
    {
        return x;
    }

    int Window::GetY()
    {
        return y;
    }

    void WINDOW_INTERNAL_Key(GLFWwindow *handle, int key, int scancode, int action, int mods)
    {
        INPUT_INTERNAL_UpdateKey((Input::Keys)key, action != GLFW_RELEASE); // Press is at the start, then Repeat and then release
    }

    void WINDOW_INTERNAL_Resize(GLFWwindow *handle, int w, int h)
    {
        Renderer::ResizeViewport({w, h});
    }

    void WINDOW_INTERNAL_Button(GLFWwindow *handle, int key, int action, int mods)
    {
        INPUT_INTERNAL_UpdateButton((Input::Buttons)key, action == GLFW_PRESS);
    }

    void WINDOW_INTERNAL_Mouse(GLFWwindow *handle, double x, double y)
    {
        INPUT_INTERNAL_UpdateMouse((float)x, (float)y);
    }

    void WINDOW_INTERNAL_Scroll(GLFWwindow *handle, double x, double y)
    {
        accumulatedScrollX += x;
        accumulatedScrollY += y;
    }
}