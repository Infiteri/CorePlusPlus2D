#include "Shader.h"

#include "Core/Logger.h"
#include "Platform/Platform.h"

#include <glad/glad.h>
#include <vector>

namespace Core
{
    static CeU32 LoadShader(const char *source, CeU32 type)
    {
        // New source casted
        const GLchar *newSrc = (const GLchar *)source;

        CeU32 shader = glCreateShader(type);
        glShaderSource(shader, 1, &newSrc, 0);
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            CE_CORE_ERROR("Shader compilation failed.");
            CE_CORE_ERROR("(%s %s) %s", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", source, infoLog.data());

            glDeleteShader(shader);
            return (GLuint)0;
        }

        return shader;
    };

    Shader::Shader(const std::string &vertex, const std::string &fragment)
    {
        CeU32 vertexShader = LoadShader(Platform::ReadFileContent(vertex).c_str(), GL_VERTEX_SHADER);
        CeU32 fragmentShader = LoadShader(Platform::ReadFileContent(fragment).c_str(), GL_FRAGMENT_SHADER);

        // Compile program
        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);

        GLint isLinked = 0;
        glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
        valid = true;
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);
            glDeleteProgram(id);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            CE_CORE_FATAL("ProgramError: %s", infoLog.data());

            valid = false;
        }

        // Delete shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        Destroy();
    }

    void Shader::Destroy()
    {

        glDeleteProgram(id);
    }

    void Shader::Use()
    {
        glUseProgram(id);
    }

    void Shader::Int(int x, const char *name)
    {
        Use();
        glUniform1i(GetUniLoc(name), x);
    }

    void Shader::Mat4(float *x, const char *name)
    {
        Use();
        glUniformMatrix4fv(GetUniLoc(name), 1, GL_FALSE, x);
    }

    void Shader::Mat4(Matrix4 *m, const char *name)
    {
        Mat4(m->data, name);
    }

    void Shader::Mat4(Matrix4 m, const char *name)
    {
        Mat4(m.data, name);
    }

    void Shader::Vec2(float x, float y, const char *name)
    {
        Use();
        glUniform2f(GetUniLoc(name), x, y);
    }

    void Shader::Vec2(Vector2 *m, const char *name)
    {
        Vec2(m->x, m->y, name);
    }

    void Shader::Vec2(Vector2 m, const char *name)
    {
        Vec2(m.x, m.y, name);
    }

    void Shader::Vec3(float x, float y, float z, const char *name)
    {
        Use();
        glUniform3f(GetUniLoc(name), x, y, z);
    }

    // void Shader::Vec3(Vector3 *m, const char *name)
    // {
    //     Vec3(m->x, m->y, m->z, name);
    // }

    // void Shader::Vec3(Vector3 m, const char *name)
    // {
    //     Vec3(m.x, m.y, m.z, name);
    // }

    void Shader::Vec4(float x, float y, float z, float w, const char *name)
    {
        Use();
        glUniform4f(GetUniLoc(name), x, y, z, w);
    }

    void Shader::Vec4(Vector4 *v, const char *name)
    {
        Vec4(v->x, v->y, v->z, v->w, name);
    }

    void Shader::Vec4(Vector4 v, const char *name)
    {
        Vec4(v.x, v.y, v.z, v.w, name);
    }

    void Shader::Float(float f, const char *name)
    {

        Use();
        glUniform1f(GetUniLoc(name), f);
    }

    CeU32 Shader::GetID()
    {
        return id;
    }

    bool Shader::IsValid()
    {
        return valid;
    }

    CeU32 Shader::GetUniLoc(const char *name)
    {
        Use();
        return glGetUniformLocation(id, name);
    }
}