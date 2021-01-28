#include "bitpch.h"

#include "Core/Application.h"
#include "Graphics/GraphicsAPI.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>

namespace Bit {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        BIT_CORE_ASSERT(!s_Instance, "Application already running!");
        s_Instance = this;

        BIT_CORE_ASSERT(glfwInit(), "GLFW did not init!");

        m_Window = Window::Create();
        m_Window->SetEventCallback(BIT_BIND_EVENT_FN(Application::EventHandling));

        BIT_CORE_ASSERT(m_Window, "Window could not be created!");

        BIT_CORE_ASSERT( (glewInit() == GLEW_OK) , "GLEW could not init!" );
    }

    Application::~Application()
    {
    }

    void Application::OnRun()
    {
        float time = glfwGetTime();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        OnUpdate(timestep);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        OnRender();

        m_Window->OnUpdate();
        //if(glfwWindowShouldClose(m_Window)) m_Running=false;
    }

    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& event)
    {
        //BIT_CORE_ERROR("OnWindowResize did stuff");
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


