#include <Bit.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Sandbox : public Bit::Application
{
public:
    Sandbox()
    {
        Bit::SimpleRenderer::Init();

        Bit::Ref<Bit::Texture2D> texture = Bit::CreateRef<Bit::Texture2D>("assets/textures/link.png");

        Bit::Entity mountain = m_Scene.CreateEntity("link");
        auto& transform = mountain.GetComponent<Bit::TransformComponent>();
        transform.Position = { 0.0f, 0.0f, 0.0f };
        transform.Scale = { 64.0f, 88.0f, 1.0f };
        mountain.AddComponent<Bit::SpriteRendererComponent>(texture);

        m_Projection = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f);
        m_View = glm::mat4(1.0f);
    }

    ~Sandbox()
    {
        Bit::SimpleRenderer::Shutdown();
    }

    void OnUpdate(Bit::Timestep& ts)
    {
        m_Ts = ts;
        m_ViewProjection = m_Projection * glm::inverse(m_View);

        Bit::GraphicsAPI::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
        Bit::GraphicsAPI::Clear();
        m_Scene.OnRender(m_ViewProjection);
    }

    void OnEvent(Bit::Event& event)
    {
        //Other Events

        //Sandbox events
        Bit::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Bit::WindowResizeEvent>(BIT_BIND_EVENT_FN(Sandbox::OnWindowResize));
        dispatcher.Dispatch<Bit::KeyPressedEvent>(BIT_BIND_EVENT_FN(Sandbox::OnKeyPressed));
        dispatcher.Dispatch<Bit::MouseScrolledEvent>(BIT_BIND_EVENT_FN(Sandbox::OnMouseScrolled));
    }

    bool OnWindowResize(Bit::WindowResizeEvent& event)
    {
        m_AspectRatio = (float)event.GetWidth()/(float)event.GetHeight();
        m_Projection = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f );
        return true;
    }

    bool OnKeyPressed(Bit::KeyPressedEvent& event)
    {

        glm::vec3 translation = { 0.0f, 0.0f, 0.0f };

        switch(event.GetKeyCode())
        {
        case Bit::Key::W:
            translation.y += 50.0f * m_Ts;
            break;
        case Bit::Key::S:
            translation.y -= 50.0f * m_Ts;
            break;
        case Bit::Key::A:
            translation.x += 50.0f * m_Ts;
            break;
        case Bit::Key::D:
            translation.x -= 50.0f * m_Ts;
            break;
        };

        m_View = glm::translate(m_View, translation);

        return true;
    }

    bool OnMouseScrolled(Bit::MouseScrolledEvent& event)
    {
        m_ZoomLevel -= event.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Projection = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f);

        return true;
    }

private:

    Bit::Timestep m_Ts;
    Bit::Scene m_Scene;
    glm::mat4 m_ViewProjection;
    glm::mat4 m_Projection;
    glm::mat4 m_View;

    float m_ZoomLevel = 100.0f;

    float m_AspectRatio = 16.0f/9.0f;

};

Bit::Application* Bit::CreateApp()
{
    return new Sandbox;
}

int main(int argc, char** argv)
{
    return BitMain(argc, argv);
}
