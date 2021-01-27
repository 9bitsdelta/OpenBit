#include "bitpch.h"

#include "Core/Application.h"

namespace Bit {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        BIT_CORE_ASSERT(!s_Instance, "Application already running!");
        s_Instance = this;

        SDL_Init(SDL_INIT_VIDEO);

        auto windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

        m_Window = SDL_CreateWindow("OpenBit", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, windowFlags);

        BIT_CORE_ASSERT(m_Window, "Window could not be created!");

        m_Context = SDL_GL_CreateContext(m_Window);

        BIT_CORE_ASSERT( (glewInit() == GLEW_OK) , "GLEW could not init!" );

        SDL_GL_SetSwapInterval(1);

    }

    Application::~Application()
    {
        SDL_GL_DeleteContext(m_Context);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    void Application::OnRun()
    {
        float time = SDL_GetTicks();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        SDL_Event event;
        OnEvent(&event);

        OnUpdate(timestep);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        OnRender();

        SDL_GL_SwapWindow(m_Window);
    }

    void Application::OnEvent(SDL_Event *event)
    {
        while(SDL_PollEvent(event)!=0)
        {
            switch(event->type)
            {
                case SDL_QUIT: OnWindowClose();
            }
        }
    }

    bool Application::OnWindowClose()
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize()
    {
        return true;
    }

}


