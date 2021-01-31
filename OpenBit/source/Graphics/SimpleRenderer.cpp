#include "bitpch.h"

#include "Graphics/SimpleRenderer.h"

namespace Bit {

    struct SimpleRendererData
    {
        Ref<Shader> shader;
        Ref<VertexArray> VAO;
    };

    static SimpleRendererData s_Data;

    void SimpleRenderer::Init()
    {
        s_Data.shader = CreateRef<Shader>("assets/shaders/texture.glsl");
        s_Data.VAO = CreateRef<VertexArray>();
        float vert[] = {
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f, 0.0f
        };
        Bit::Ref<Bit::VertexBuffer> vertexBuffer = Bit::CreateRef<Bit::VertexBuffer>(vert, sizeof(vert));
        Bit::BufferLayout layout = {
            { Bit::ShaderDataType::Float3, "a_Position" },
            { Bit::ShaderDataType::Float2, "a_UV" },
        };
        vertexBuffer->SetLayout(layout);
        s_Data.VAO->SetVertexBuffer(vertexBuffer);
        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
        Bit::Ref<Bit::IndexBuffer> indexBuffer = Bit::CreateRef<Bit::IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
        s_Data.VAO->SetIndexBuffer(indexBuffer);
    }

    void SimpleRenderer::BeginScene(const glm::mat4& camera)
    {
        s_Data.shader->Bind();
        s_Data.shader->UploadUniformMat4("u_ViewProjection", camera);
    }

    void SimpleRenderer::EndScene()
    {

    }

    void SimpleRenderer::Submit(const glm::mat4& transform, const Ref<Texture2D>& texture)
    {
        s_Data.VAO->Bind();
        s_Data.shader->Bind();
        s_Data.shader->UploadUniformMat4("u_Transform", transform);
        texture->Bind();
        GraphicsAPI::DrawIndexed(s_Data.VAO);
    }

}