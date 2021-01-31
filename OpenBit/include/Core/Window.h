#pragma once

#include "Core/Base.h"
#include "Core/Event.h"

namespace Bit {

    struct WindowProps
    {
        std::string Title;
        uint32_t Width, Height;
    
        WindowProps(std::string t = "OpenBit",
                    uint32_t w = 800,
                    uint32_t h = 600)
            : Title(t), Width(w), Height(h)
        {

        }
    };

    using EventCallbackFn = std::function<void(Event&)>;

    class Window
    {
    public:

        Window(const WindowProps& props = WindowProps());
        ~Window();

        static Scope<Window> Create(const WindowProps& props = WindowProps());

        void SetEventCallback(const EventCallbackFn& callback);
        void SetVSync(bool enabled);
        void OnUpdate();

        float GetTime() const;
        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
        bool IsVSync() const;
        void* GetNativeWindow() const;
    };

}