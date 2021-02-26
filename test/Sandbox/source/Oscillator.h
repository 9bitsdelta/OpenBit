#pragma once

#include <Bit.h>

class Oscillator
{
public:
    void Init();

    void Shutdown();

    void OnUpdate(Bit::Timestep& ts);

    void OnEvent(Bit::Event& event);

private:
    // Bit::Camera m_Camera;
    // Bit::Scene m_Scene;
};