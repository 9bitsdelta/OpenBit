#include "Bit.h"

#include <iostream>

class Sandbox : public Bit::Application
{
public:
    Sandbox()
    {
        m_VAO = Bit::CreateRef<Bit::VertexArray>();

        float vert[] = {
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f
        };

        Bit::Ref<Bit::VertexBuffer> vertexBuffer = Bit::CreateRef<Bit::VertexBuffer>(vert, sizeof(vert));

        Bit::BufferLayout layout = {
            { Bit::ShaderDataType::Float3, "a_Position" },
        };
        vertexBuffer->SetLayout(layout);
        m_VAO->SetVertexBuffer(vertexBuffer);

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
        Bit::Ref<Bit::IndexBuffer> indexBuffer = Bit::CreateRef<Bit::IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
        m_VAO->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            void main()
            {
                gl_Position = vec4(a_Position, 1.0);	
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            void main()
            {
                color = vec4(1.0, 1.0, 1.0, 1.0);
            }
        )";

        m_Shader = Bit::CreateRef<Bit::Shader>("VertexPosColor", vertexSrc, fragmentSrc);

        std::string flatColorShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
            }
        )";

        std::string flatColorShaderFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            uniform vec3 u_Color;

            void main()
            {
                color = vec4(u_Color, 1.0);
            }
        )";

        m_FlatColorShader = Bit::CreateRef<Bit::Shader>("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

    }

    ~Sandbox()
    {

    }

    void OnUpdate(Bit::Timestep& ts)
    {
        //BIT_TRACE("Timestep in ms: {}", ts.GetMilliseconds() );
        //BIT_TRACE("Timestep in fps: {}", 1000.0f / ts.GetMilliseconds());
    }

    void OnRender()
    {
        m_VAO->Bind();
        m_Shader->Bind();
        Bit::GraphicsAPI::DrawIndexed(m_VAO);
    }

private:
    Bit::Ref<Bit::VertexArray> m_VAO;
    Bit::Ref<Bit::Shader> m_Shader;
    Bit::Ref<Bit::Shader> m_FlatColorShader;
};

Bit::Application* Bit::CreateApp()
{
    return new Sandbox;
}

int main(int argc, char** argv)
{
    return BitMain(argc, argv);
}