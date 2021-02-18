#include <Bit.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Test.h"
#include "Oscillator.h"

class Sandbox : public Bit::Application
{
public:
    Sandbox()
    {
        Bit::SpriteRenderer::Init();
        
        m_Camera.SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        m_Camera.SetPosition({ 0.0f, 0.0f, 0.0f });
        m_Camera.SetType(Bit::Projection::Orthographic);

        testLayer.Init(&m_Camera);
        osc.Init();
    }

    ~Sandbox()
    {
        testLayer.Shutdown();
        osc.Shutdown();
        Bit::SpriteRenderer::Shutdown();
    }

    void OnUpdate(Bit::Timestep& ts)
    {
        glm::vec3 translation = m_Camera.GetPosition();
        float yaw = m_Camera.GetYaw();
        if (Bit::Input::IsKeyPressed(Bit::Key::Space))     translation.y += m_Speed * ts;
        if (Bit::Input::IsKeyPressed(Bit::Key::LeftShift)) translation.y -= m_Speed * ts;
        if (Bit::Input::IsKeyPressed(Bit::Key::A))         translation -= m_Speed * ts * m_Camera.GetRightDirection();
        if (Bit::Input::IsKeyPressed(Bit::Key::D))         translation += m_Speed * ts * m_Camera.GetRightDirection();
        if (Bit::Input::IsKeyPressed(Bit::Key::W))         translation += m_Speed * ts * m_Camera.GetForwardDirection();
        if (Bit::Input::IsKeyPressed(Bit::Key::S))         translation -= m_Speed * ts * m_Camera.GetForwardDirection();
        if (Bit::Input::IsKeyPressed(Bit::Key::Q))         yaw -= 1.5f * ts;
        if (Bit::Input::IsKeyPressed(Bit::Key::E))         yaw += 1.5f * ts;
        m_Camera.SetPosition(translation);
        m_Camera.SetRotation(0.0f, yaw);

        testLayer.OnUpdate(ts);
        osc.OnUpdate(ts);
    }

    void OnEvent(Bit::Event& event)
    {
        //Other Events
        testLayer.OnEvent(event);
        osc.OnEvent(event);

        //Sandbox events
        Bit::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Bit::WindowResizeEvent>(BIT_BIND_EVENT_FN(Sandbox::OnWindowResize));
        dispatcher.Dispatch<Bit::MouseScrolledEvent>(BIT_BIND_EVENT_FN(Sandbox::OnMouseScrolled));
    }

    bool OnWindowResize(Bit::WindowResizeEvent& event)
    {
        m_AspectRatio = (float)event.GetWidth()/(float)event.GetHeight();
        m_Camera.SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        
        return true;
    }

    bool OnMouseScrolled(Bit::MouseScrolledEvent& event)
    {
        m_ZoomLevel -= event.GetYOffset() * 1.5f;
        m_ZoomLevel = std::max(m_ZoomLevel, 1.25f);
        m_Camera.SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return true;
    }

private:
    Oscillator osc;
    TestLayer testLayer;

    Bit::Timestep m_Ts;
    Bit::Camera m_Camera;

    float m_ZoomLevel = 50.0f;
    float m_AspectRatio = 16.0f/9.0f;
    const float m_Speed = 30.0f;
};

Bit::Application* Bit::CreateApp()
{
    return new Sandbox;
}

int main(int argc, char** argv)
{
    return BitMain(argc, argv);
}
