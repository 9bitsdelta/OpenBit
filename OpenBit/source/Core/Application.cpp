#include "bitpch.h"

#include "Core/Application.h"
#include "Graphics/API/GraphicsAPI.h"

namespace Bit {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        BIT_CORE_ASSERT(!s_Instance, "Application already running!");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(BIT_BIND_EVENT_FN(Application::EventHandling));

        BIT_CORE_ASSERT(m_Window, "Window could not be created!");

        GraphicsAPI::Init();
    }

    Application::~Application()
    {
    }

    void Application::OnRun()
    {
        float time = m_Window->GetTime();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        OnUpdate(timestep);

        GraphicsAPI::SetClearColor( {0.1f, 0.1f, 0.1f, 1.0f} );
        GraphicsAPI::Clear();

        OnRender();

        m_Window->OnUpdate();
    }

    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& event)
    {
        GraphicsAPI::SetViewport(0, 0, event.GetWidth(), event.GetHeight());
        
        return true;
    }

    void Application::EventHandling(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIT_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIT_BIND_EVENT_FN(Application::OnWindowResize));

        OnEvent(event);
    }

}


