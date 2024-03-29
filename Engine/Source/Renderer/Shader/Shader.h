#pragma once

#include "Base.h"
#include "Math/Matrix4.h"
#include "Math/Vectors.h"

#include <string>

namespace Core
{
    class CE_API Shader
    {
    private:
        CeU32 id;
        bool valid = false;

    public:
        Shader(const std::string &vertex, const std::string &fragment);
        ~Shader();

        void Destroy();

        void Use();
        void Int(int x, const char *name);
        void Mat4(float *x, const char *name);
        void Mat4(Matrix4 *m, const char *name);
        void Mat4(Matrix4 m, const char *name);

        void Vec2(float x, float y, const char *name);
        void Vec2(Vector2 *m, const char *name);
        void Vec2(Vector2 m, const char *name);

        void Vec3(float x, float y, float z, const char *name);
        // void Vec3(Vector3 *m, const char *name);
        // void Vec3(Vector3 m, const char *name);

        void Vec4(float x, float y, float z, float w, const char *name);
        void Vec4(Vector4 *m, const char *name);
        void Vec4(Vector4 m, const char *name);

        void Float(float f, const char *name);

        CeU32 GetID();
        bool IsValid();
        CeU32 GetUniLoc(const char *name);
    };
}