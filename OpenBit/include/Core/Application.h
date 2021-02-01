#pragma once

#include "Core/Window.h"
#include "Core/Timestep.h"
#include "Core/Event.h"

int BitMain(int argc, char** argv);

namespace Bit {

    class Application
    {
    public:

        Application();
        virtual ~Application();

        virtual void OnEvent(Event& event) {}
        virtual void OnUpdate(Timestep& ts) {}

    private:
        void OnRun();
        bool IsRunning() { return m_Running; }
        
        void EventHandling(Event& event);

        bool OnWindowClose(WindowCloseEvent& event);
        bool OnWindowResize(WindowResizeEvent& event);

    private:
        bool m_Running = true;
        Timestep m_LastFrameTime = 0;
        Scope<Window> m_Window;

    private:
        static Application* s_Instance;
        friend int ::BitMain(int argc, char** argv);
    };
    
    Application* CreateApp();

}
