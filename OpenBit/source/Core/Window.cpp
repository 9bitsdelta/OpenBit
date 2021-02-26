#include "bitpch.h"
#include "Core/Window.h"

#include <GLFW/glfw3.h>

namespace Bit {

    struct WindowData
    {
        //GLFWwindow* Window;
        std::string Title;
        uint32_t Width, Height;
        bool VSync;
        EventCallbackFn EventCallback;
    };

    static WindowData s_Data;
    static GLFWwindow* s_Window;

    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        BIT_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Scope<Window> Window::Create(const WindowProps& props)
    {
        return CreateScope<Window>(props);
    }

    Window::Window(const WindowProps& props)
    {
        s_Data.Title = props.Title;
        s_Data.Width = props.Width;
        s_Data.Height = props.Height;

        BIT_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0)
        {
            int success = glfwInit();
            BIT_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {

        #if defined(BIT_DEBUG)
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        #endif
        
            s_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
            ++s_GLFWWindowCount;
        }

        glfwMakeContextCurrent(s_Window);

        glfwSetWindowUserPointer(s_Window, &s_Data);
        SetVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(s_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(s_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(s_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(s_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(s_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(s_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(s_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }

    Window::~Window()
    {
        glfwDestroyWindow(s_Window);
        --s_GLFWWindowCount;

        if (s_GLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(s_Window);
    }

    void Window::SetEventCallback(const EventCallbackFn& callback)
    {
        s_Data.EventCallback = callback;
    }

    void Window::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        s_Data.VSync = enabled;
    }

    bool Window::IsVSync() const
    {
        return s_Data.VSync;
    }

    void* Window::GetNativeWindow() const
    {
        return s_Window;
    }

    float Window::GetTime() const
    {
        return glfwGetTime();
    }

    uint32_t Window::GetWidth() const
    {
        return s_Data.Width;
    }

    uint32_t Window::GetHeight() const
    {
        return s_Data.Height;
    }

}
