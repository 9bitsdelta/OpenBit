#pragma once

#include "Core/Timestep.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

int BitMain(int argc, char** argv);

namespace Bit {

    class Application
    {
    public:

        Application();
        virtual ~Application();

    private:
        void OnRun();
        bool IsRunning() { return m_Running; }
        
        void OnEvent(SDL_Event* ev);
        
        virtual void OnUpdate(Timestep& ts) = 0;
        
        virtual void OnRender() {}

        bool OnWindowClose();
        bool OnWindowResize();
        
    private:
        bool m_Running = true;
        Timestep m_LastFrameTime = 0;
        SDL_Window* m_Window;
        SDL_GLContext m_Context;

    private:
        static Application* s_Instance;
        friend int ::BitMain(int argc, char** argv);
    };
    
    Application* CreateApp();

}
