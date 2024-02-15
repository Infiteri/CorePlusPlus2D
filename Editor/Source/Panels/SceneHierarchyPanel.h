#pragma once

namespace Core
{
    class Actor;
    class SceneHierarchyPanel
    {
    public:
        Actor *selectionContext = nullptr; /// @brief Selected actor, if nullptr than none is selected.

        SceneHierarchyPanel(){};
        ~SceneHierarchyPanel(){};

        void RenderGUIActor(Actor *a);
        void RenderGUIActorProperties(Actor *a);

        void RenderGUI(); /// @brief Will render the active scene's hierarchy
    };
}
