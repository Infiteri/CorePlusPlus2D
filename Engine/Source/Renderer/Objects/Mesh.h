#pragma once

#include "Base.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Math/Transform.h"
#include "Renderer/Material/Material.h"

namespace Core
{
    class CE_API Mesh
    {
    private:
        VertexArray *VArray;

        Material *material;
        Transform transform;

    public:
        Mesh();
        ~Mesh();

        void Render();

        inline Transform *GetTransform() { return &transform; };
        inline Material *GetMaterial() { return material; };
    };
}