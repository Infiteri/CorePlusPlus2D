#include "Core.h"
#include "Core/EntryPoint.h"

class Sandbox : public Core::Application
{
public:
    Sandbox(){};
    ~Sandbox(){};

    void Update()
    {
        if (Core::Input::GetKey(Core::Input::A))
        {
        }
    };
};

Core::Application *Core::CreateApplication()
{
    return new Sandbox();
};