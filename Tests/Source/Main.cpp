#include "Core.h"
#include "Tests/CameraSystemTest.h"
#include "Tests/SceneSavingTest.h"
#include "Tests/Test.h"
#include "Core/EntryPoint.h"

static std::vector<Core::Test *> tests;

class MainTestApplication : public Core::Application
{
public:
    MainTestApplication(){};
    ~MainTestApplication(){};

    void Init()
    {
        tests.push_back(new CameraSystemTest());
    };
    void Update()
    {
        for (int i = 0; i < tests.size(); i++)
        {
            auto t = tests[i];
            if (!t)
                return;
            bool res = t->Run();

            if (!res)
                CE_CORE_ERROR("%s: Failed Test.", t->name.c_str());
            else
                CE_CORE_INFO("%s: Success Test.", t->name.c_str());

            delete t;
            tests.erase(tests.begin() + i);
        }
    };
    void Shutdown(){};
};

namespace Core
{
    Application *CreateApplication(Core::EngineConfiguration *config)
    {
        return new MainTestApplication();
    }
}