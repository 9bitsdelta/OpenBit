#include "Test.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

    void TestLayer::Init(Bit::Ref<Bit::Camera> camera)
    {
        m_Camera = camera;
        Bit::Ref<Bit::Texture2D> texture = Bit::Texture2D::Create("assets/textures/link.png");
        Bit::Ref<Bit::Texture2D> texture2 = Bit::Texture2D::Create("assets/textures/link2.png");
        
        m_Scene.SetCamera(m_Camera);

        m_Link1 = m_Scene.CreateEntity("link1");
        auto& transform = m_Link1.GetComponent<Bit::TransformComponent>();
        transform.Scale    = { (float)texture->GetWidth(), (float)texture->GetHeight(), 1.0f };
        transform.Position = { 0.0f, 0.0f, -21.0f };
        m_Link1.AddComponent<Bit::SpriteComponent>(texture2);

        m_Link2 = m_Scene.CreateEntity("link2");
        auto& transform2 = m_Link2.GetComponent<Bit::TransformComponent>();
        transform2.Scale    = { (float)texture->GetWidth(), (float)texture->GetHeight(), 1.0f };
        transform2.Position = { 18.0f, 0.0f, -20.0f };
        m_Link2.AddComponent<Bit::SpriteComponent>(texture);

        m_Link3 = m_Scene.CreateEntity("link3");
        auto& transform3 = m_Link3.GetComponent<Bit::TransformComponent>();
        transform3.Scale    = { (float)texture->GetWidth(), (float)texture->GetHeight(), 1.0f };
        transform3.Position = { 7.0f, 0.0f, -23.0f };
        m_Link3.AddComponent<Bit::SpriteComponent>(texture);

        auto m_Link4 = m_Scene.CreateEntity("link4");
        auto& transform4 = m_Link4.GetComponent<Bit::TransformComponent>();
        transform4.Scale = { (float)texture->GetWidth(), (float)texture->GetHeight(), 1.0f };
        transform4.Position = { 0.0f, 0.0f, -25.0f };
        m_Link4.AddComponent<Bit::SpriteComponent>(texture2);

    }

    void TestLayer::Shutdown()
    {

    }

    void TestLayer::OnUpdate(Bit::Timestep& ts)
    {
        // auto& transform = m_Link1.GetComponent<Bit::TransformComponent>();
        // if(Bit::Input::IsKeyPressed(Bit::Key::Up)) transform.Position.z -= m_Speed * ts;
        // if(Bit::Input::IsKeyPressed(Bit::Key::Down)) transform.Position.z += m_Speed * ts;

        m_Scene.OnUpdate(ts);
    }

    void TestLayer::OnEvent(Bit::Event& event)
    {

    }