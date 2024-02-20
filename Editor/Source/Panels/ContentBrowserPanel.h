#pragma once

#include <string>

namespace Core
{
    class ContentBrowserPanel
    {
    public:
        std::string BaseDirectoryPath;

        ContentBrowserPanel(){};
        ~ContentBrowserPanel(){};

        void OnImGuiRender();
    };
}