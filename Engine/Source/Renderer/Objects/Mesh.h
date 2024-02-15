#pragma once

#include "Base.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Math/Transform.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Geometry/Geometry.h"

namespace Core
{
    class CE_API Mesh
    {
    private:
        VertexArray *VArray;

        Geometry *geometry;
        Material *material;
        bool isMaterialUnique;

        void InitVertexArray();

    public:
        Mesh();
        ~Mesh();

        void Render();

        /// @brief Will set material from a file with the passed file name. Old material will be released, by default, a white material is loaded.
        /// @param filename The material filename.
        void SetMaterial(const std::string &filename);

        /// @brief Sets a material from config. Will be marked as unique
        /// @param config The config to use.
        void SetMaterial(Material::Configuration *config);

        /// @brief Will set the meshes geometry. Remember if for some reasons the geometry is deleted by user, side effects exist.
        /// @note For no errors, call SetGeometry(new WANTED_GEOMETRY(ARGUMENTS)); So that the new geometry created is owned by the mesh.
        /// @param geometry The newly wanted geometry.
        void SetGeometry(Geometry *geometry);

        inline Material *GetMaterial() { return material; };
        inline Geometry *GetGeometry() { return geometry; };

        inline bool IsMaterialUnique() { return isMaterialUnique; };
    };
}