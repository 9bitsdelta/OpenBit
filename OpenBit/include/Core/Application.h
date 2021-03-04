#pragma once

#include "Core/Window.h"
#include "Core/Timestep.h"
#include "Core/Event.h"

#include "ImGui/ImGuiSys.h"

int BitMain(int argc, char** argv);

namespace Bit {

    class Application
    {
    public:

        Application(const std::string& windowTitle = "OpenBit");
        virtual ~Application();

        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }
        ImGuiSys& GetImGui() { return m_ImGui; }

        virtual void OnEvent(Event& event) {}
        virtual void OnUpdate(Timestep& ts) {}
        virtual void OnImGuiRender() {}

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

        ImGuiSys m_ImGui;

    private:
        static Application* s_Instance;
        friend int ::BitMain(int argc, char** argv);
    };
    
    Application* CreateApp();

}
