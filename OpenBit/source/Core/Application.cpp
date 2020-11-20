#include "bitpch.h"

#include "Core/Application.h"

namespace Bit {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        //ASSERT s_Instance;
        s_Instance = this;
    }

    Application::~Application()
    {

    }

    void Application::OnRun()
    {
        float time = 0;
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        OnUpdate(timestep);
    }

    void Application::Close()
    {
        m_Running = false;
    }

}


