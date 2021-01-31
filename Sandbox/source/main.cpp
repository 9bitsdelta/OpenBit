#include <Bit.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Sandbox : public Bit::Application
{
public:
    Sandbox()
    {
        Bit::SimpleRenderer::Init();

        Bit::Ref<Bit::Texture2D> texture = Bit::CreateRef<Bit::Texture2D>("assets/textures/mountain.bmp");

        Bit::Entity mountain = m_Scene.CreateEntity("Mountain");
        auto& transform = mountain.GetComponent<Bit::TransformComponent>();
        transform.Position = { -200.0f, -150.0f, 0.0f };
        transform.Scale = { 400.0f, 300.0f, 1.0f };
        mountain.AddComponent<Bit::SpriteRendererComponent>(texture);

        m_Projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f);
        m_View = glm::mat4(1.0f);
    }

    ~Sandbox()
    {
        Bit::SimpleRenderer::Shutdown();
    }

    void OnUpdate(Bit::Timestep& ts)
    {
        m_Ts = ts;
        m_ViewProjection = m_Projection * m_View;
    }

    void OnRender()
    {
        m_Scene.OnRender(m_ViewProjection);
    }

    void OnEvent(Bit::Event& event)
    {
        //Other Events

        //Sandbox events
        Bit::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Bit::WindowResizeEvent>(BIT_BIND_EVENT_FN(Sandbox::OnWindowResize));
        dispatcher.Dispatch<Bit::KeyPressedEvent>(BIT_BIND_EVENT_FN(Sandbox::OnKeyPressed));
    }

    bool OnWindowResize(Bit::WindowResizeEvent& event)
    {
        m_Projection = glm::ortho(event.GetWidth()*-0.5f, event.GetWidth()*0.5f, (float)event.GetHeight()*(-0.5f), (float)event.GetHeight()*0.5f );
        return true;
    }

    bool OnKeyPressed(Bit::KeyPressedEvent& event)
    {

        glm::vec3 translation = { 0.0f, 0.0f, 0.0f };

        switch(event.GetKeyCode())
        {
        case Bit::Key::W:
            translation.y += 100.0f * m_Ts;
            break;
        case Bit::Key::S:
            translation.y -= 100.0f * m_Ts;
            break;
        case Bit::Key::A:
            translation.x += 100.0f * m_Ts;
            break;
        case Bit::Key::D:
            translation.x -= 100.0f * m_Ts;
            break;
        };

        m_View = glm::translate(m_View, translation);

        return true;
    }

private:

    Bit::Timestep m_Ts;
    Bit::Scene m_Scene;
    glm::mat4 m_ViewProjection;
    glm::mat4 m_Projection;
    glm::mat4 m_View;

};

Bit::Application* Bit::CreateApp()
{
    return new Sandbox;
}

int main(int argc, char** argv)
{
    return BitMain(argc, argv);
}
