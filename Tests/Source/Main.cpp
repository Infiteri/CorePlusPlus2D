#include "Core.h"
#include "Tests/CameraSystemTest.h"
#include "Core/EntryPoint.h"

using namespace Core;

static std::vector<Test *> tests;

class MainTestApplication : public Application
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

Core::Application *Core::CreateApplication()
{
    return new MainTestApplication();
}