#pragma once

#include <Bit.h>

class TestLayer
{
public:

    void Init(Bit::Ref<Bit::Camera> camera);
    void Shutdown();

    void OnUpdate(Bit::Timestep& ts);
    void OnEvent(Bit::Event& event);

private:

    Bit::Entity m_Link1;
    Bit::Entity m_Link2;
    Bit::Entity m_Link3;

    Bit::Scene m_Scene;
    Bit::Ref<Bit::Camera> m_Camera;

    const float m_Speed = 30.0f;
};

