#pragma once

#include "Base.h"

namespace Core
{

    /// @brief Structure that represents the viewport of the renderer.
    struct Viewport
    {
        int width;
        int height;

        Viewport(int w, int h)
        {
            width = w;
            height = h;
        };

        Viewport(const Viewport &v)
        {
            width = v.width;
            height = v.height;
        };
    };

    class CE_API Renderer
    {
    public:
        Renderer(){};
        ~Renderer(){};

        static void ResizeViewport(const Viewport &new_viewport);

        /// @brief DO NOT CALL ON YOUR OWN
        static void RegenerateObjectsWithNewViewport();

        static void Init();
        static void BeginFrame();
        static void Render();
        static void EndFrame();
        static void DrawToScreen();
        static void Shutdown();
    };
}