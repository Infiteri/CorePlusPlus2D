#pragma once

#include "Core.h"

class TestScript : public Core::ActorScript
{
public:
    TestScript(){};
    ~TestScript(){};

    void OnUpdate();
};

CE_EXPORT_ACTOR_CLASS(TestScript);
