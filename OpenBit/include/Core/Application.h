#pragma once

#include "Core/Timestep.h"

int BitMain(int argc, char** argv);

namespace Bit {

    class Application
    {
    public:

        Application();
        virtual ~Application();

        void Close();

    private:
        void OnRun();
        bool IsRunning() { return m_Running; }
        
        virtual void OnUpdate(Timestep& ts) = 0;
        
    private:
        bool m_Running = true;
        Timestep m_LastFrameTime = 0;
    private:
        static Application* s_Instance;
        friend int ::BitMain(int argc, char** argv);
    };
    
    Application* CreateApp();

}
