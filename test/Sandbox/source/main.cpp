#include <Bit.h>

#include "Test.h"

#include <sol.hpp>

class Sandbox : public Bit::Application
{
public:
    Sandbox()
    {
        m_Camera->SetPerspectiveProjection(glm::radians(45.0f), m_AspectRatio, 1.0f, 100.0f);
        testLayer.Init(m_Camera);

        // LUA INIT

        const std::string script = R"(
            x = 42

            print('Hello Script!')

            function OnUpdate()
                return "Hello Lua!"
            end

        )";

        m_Lua.open_libraries(sol::lib::base);

        m_Lua.script(script.data());


        int x = m_Lua["x"];
        std::function<const char*()> onUpdateFunc = m_Lua["OnUpdate"];
        BIT_WARN("Retrieved x = {}", x);
        BIT_WARN("Retrieved output of OnUpdate(): {}", onUpdateFunc() );
    }

    ~Sandbox()
    {
        testLayer.Shutdown();
    }

    void OnUpdate(Bit::Timestep& ts)
    {
        glm::vec3 translation = m_Camera->GetPosition();
        float yaw = m_Camera->GetYaw();

        if (Bit::Input::IsKeyPressed(Bit::Key::Space))
            translation.y += m_Speed * ts;
        if (Bit::Input::IsKeyPressed(Bit::Key::LeftShift))
            translation.y -= m_Speed * ts;
        if (Bit::Input::IsKeyPressed(Bit::Key::A))
            translation -= m_Speed * ts * m_Camera->GetRightDirection();
        if (Bit::Input::IsKeyPressed(Bit::Key::D))
            translation += m_Speed * ts * m_Camera->GetRightDirection();
        if (Bit::Input::IsKeyPressed(Bit::Key::W))
            translation += m_Speed * ts * m_Camera->GetForwardDirection();
        if (Bit::Input::IsKeyPressed(Bit::Key::S))
            translation -= m_Speed * ts * m_Camera->GetForwardDirection();
        if (Bit::Input::IsKeyPressed(Bit::Key::Q))
            yaw -= 1.5f * ts;
        if (Bit::Input::IsKeyPressed(Bit::Key::E))
            yaw += 1.5f * ts;

        m_Camera->SetPosition(translation);
        m_Camera->SetRotation(0.0f, yaw, 0.0f);

        testLayer.OnUpdate(ts);

        // LUA UPDATE

    }

    void OnEvent(Bit::Event& event)
    {
        //Other Events
        testLayer.OnEvent(event);

        //Sandbox events
        Bit::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Bit::WindowResizeEvent>(BIT_BIND_EVENT_FN(Sandbox::OnWindowResize));
        dispatcher.Dispatch<Bit::MouseScrolledEvent>(BIT_BIND_EVENT_FN(Sandbox::OnMouseScrolled));
    }

    bool OnWindowResize(Bit::WindowResizeEvent& event)
    {
        m_AspectRatio = (float)event.GetWidth()/(float)event.GetHeight();
        m_Camera->SetPerspectiveProjection(glm::radians(45.0f), m_AspectRatio, 1.0f, 100.0f);

        return true;
    }

    bool OnMouseScrolled(Bit::MouseScrolledEvent& event)
    {
        m_ZoomLevel -= event.GetYOffset() * 1.5f;
        m_ZoomLevel = std::max(m_ZoomLevel, 1.25f);

        return true;
    }

private:
    TestLayer testLayer;

    sol::state m_Lua;

    Bit::Timestep m_Ts;
    Bit::Ref<Bit::Camera> m_Camera = Bit::Camera::Create(Bit::Projection::Perspective);

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
