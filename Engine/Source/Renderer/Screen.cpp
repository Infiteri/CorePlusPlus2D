#include "Screen.h"
#include "Core/Memory/CeMemory.h"
#include "Shader/ShaderSystem.h"
#include <glad/glad.h>

namespace Core
{

    static float ScreenVertices[] = {
        // positions   // texCoords
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 1.0f};

    void GPUScreen::Create()
    {
        ScreenShader = ShaderSystem::Get("EngineResources/Shaders/Screen");
        ScreenVertexArray = new VertexArray();
        ScreenVertexArray->GenVertexBuffer(ScreenVertices, sizeof(ScreenVertices));
        ScreenVertexArray->GetVertexBuffer()->AddLayout(0, 0, 2);
        ScreenVertexArray->GetVertexBuffer()->AddLayout(1, 2, 2);

        FrameBufferSpecification spec;
        spec.width = viewport->width;
        spec.height = viewport->height;

        spec.renderPassSpecificationCount = 2;
        spec.renderPassSpecifications = (RenderPassSpecification *)CeMemory::Allocate(sizeof(RenderPassSpecification) * spec.renderPassSpecificationCount);
        spec.renderPassSpecifications[0].textureType = RenderPassTextureType::Rgba8;
        spec.renderPassSpecifications[1].textureType = RenderPassTextureType::Depth;

        ScreenFramebuffer = new FrameBuffer(spec);
    }

    void GPUScreen::EndGPUSideFrame()
    {
        ScreenFramebuffer->Unbind();

        // BAD IF GREEN
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GPUScreen::DrawImageToScreen()
    {
        ScreenShader->Use();
        ScreenVertexArray->Bind();

        // Bind texture
        RenderPassSpecification *renderPass = ScreenFramebuffer->GetRenderPass(0);
        glActiveTexture(GL_TEXTURE0 + renderPass->index);
        glBindTexture(GL_TEXTURE_2D, renderPass->id);
        ScreenShader->Int(renderPass->index, "uScreenTexture");

        ScreenVertexArray->GetVertexBuffer()->Bind();
        ScreenVertexArray->GetVertexBuffer()->Draw();
    }
}