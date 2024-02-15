#pragma once

#include "Base.h"
#include "Math/Vectors.h"
#include <vector>

namespace Core
{
    struct Vertex3D
    {
        Vector3 Position;
        Vector2 UV;
    };

    class CE_API Geometry
    {
    public:
        enum Type
        {
            None,
            Square
        };

    protected:
        std::vector<Vertex3D> vertices;
        std::vector<CeU32> indices;
        Type type = None;

    public:
        Geometry(){};
        ~Geometry(){};

        inline Vertex3D *GetVertices() { return vertices.data(); };
        inline CeU32 *GetIndices() { return indices.data(); };

        inline CeU32 GetVerticesSize() { return vertices.size() * sizeof(float); };
        inline CeU32 GetIndicesSize() { return indices.size() * sizeof(CeU32); };

        inline Type GetType() { return type; };
    };

    class CE_API SquareGeometry : public Geometry
    {
    public:
        float Width;
        float Height;

        SquareGeometry(float width, float height);
        ~SquareGeometry();
    };
}