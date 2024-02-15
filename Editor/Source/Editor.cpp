#include "Core.h"
#include <imgui.h>
#include "Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Core
{
    class Editor : public Application
    {
    public:
        Editor(){};
        ~Editor(){};

        void Init()
        {
            LayerStack::PushLayer(new EditorLayer());
        };
    };

    Application *CreateApplication(EngineConfiguration *config)
    {
        config->WindowInformation.acceptDefaultWindowResizeCallback = false;
        return new Editor();
    };
}