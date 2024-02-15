#include "Window.h"
#include "Renderer/Renderer.h"
#include "GLFW/glfw3.h"

#include "Input.h"

namespace Core
{
    void WINDOW_INTERNAL_Key(GLFWwindow *handle, int key, int scancode, int action, int mods);
    void WINDOW_INTERNAL_Resize(GLFWwindow *handle, int w, int h);

    Window::Window(const WindowInformation &information)
    {
        info.x = information.x;
        info.y = information.y;
        info.width = information.width;
        info.height = information.height;
        info.title = information.title;
        info.mode = information.mode;
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

            if (info.acceptDefaultWindowResizeCallback)
                glfwSetWindowSizeCallback(handle, WINDOW_INTERNAL_Resize);
        }

        glfwGetWindowSize(handle, &width, &height);
        Renderer::ResizeViewport({width, height});
    }

    Window::~Window()
    {
        glfwDestroyWindow(handle);
        glfwTerminate();

        glfwGetWindowSize(handle, &width, &height);
    }

    bool Window::ShouldRun()
    {
        return !glfwWindowShouldClose(handle);
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(handle);
    }

    int Window::GetWidth()
    {
        return width;
    }

    int Window::GetHeight()
    {
        return height;
    }

    void WINDOW_INTERNAL_Key(GLFWwindow *handle, int key, int scancode, int action, int mods)
    {
        INPUT_INTERNAL_UpdateKey((Input::Keys)key, action != GLFW_RELEASE); // Press is at the start, then Repeat and then release
    }

    void WINDOW_INTERNAL_Resize(GLFWwindow *handle, int w, int h)
    {
        Renderer::ResizeViewport({w, h});
    }
}