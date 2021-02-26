#include "bitpch.h"
#include "Graphics/PrimitiveRenderer.h"

#include <glad/glad.h>

namespace Bit {

    struct PrimitiveRendererData
    {
        Ref<Shader> Shader;
    };

    static PrimitiveRendererData s_Data;

    void PrimitiveRenderer::Init()
    {
        const std::string shaderVertSrc = R"(
            #version 450
            
            layout(location = 0) in vec3 a_Position;
            
            uniform mat4 u_Transform = mat4(1.0);
            uniform mat4 u_ViewProjection;
            
            void main()
            {
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            })";

        const std::string shaderFragSrc = R"(
            #version 450

            layout(location = 0) out vec4 color;

            uniform vec4 u_Color;

            void main()
            {
                color = u_Color;
            })";

        s_Data.Shader = Shader::Create("Primitive", shaderVertSrc, shaderFragSrc);
    }

    void PrimitiveRenderer::Shutdown()
    {
        s_Data.~PrimitiveRendererData();
    }

    void PrimitiveRenderer::BeginScene(const glm::mat4& cam)
    {
        s_Data.Shader->Bind();
        s_Data.Shader->UploadUniformMat4("u_ViewProjection", cam);
    }

    void PrimitiveRenderer::EndScene()
    {
        s_Data.Shader->Unbind();
    }

    void PrimitiveRenderer::SetShader(const Ref<Shader>& shader) { s_Data.Shader = shader; }
    Ref<Shader>& PrimitiveRenderer::GetShader() { return s_Data.Shader; }

    void PrimitiveRenderer::Draw(const DrawMethod& type, std::vector<float> points, std::vector<uint32_t> indices, const glm::vec4& color)
    {
        Ref<VertexArray> arr = VertexArray::Create();
        Ref<VertexBuffer> buff = VertexBuffer::Create(points.data(), points.size()*sizeof(float));
        buff->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
        });
        Ref<IndexBuffer> index = IndexBuffer::Create(indices.data(), indices.size());
        arr->SetVertexBuffer(buff);
        arr->SetIndexBuffer(index);
        s_Data.Shader->UploadUniformFloat4("u_Color", color);
        GraphicsAPI::DrawIndexed(type, arr, arr->GetIndexBuffer()->GetCount());
    }

}