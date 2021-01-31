#include "bitpch.h"
#include "Graphics/API/GraphicsAPI.h"

#include "glad/glad.h"

#include "Core/Log.h"

namespace Bit {

    void OpenGLLogMessage(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int length, const char* message, const void* userParam)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         BIT_CORE_CRITICAL(message); return;
            case GL_DEBUG_SEVERITY_MEDIUM:       BIT_CORE_ERROR(message); return;
            case GL_DEBUG_SEVERITY_LOW:          BIT_CORE_WARN(message); return;
            case GL_DEBUG_SEVERITY_NOTIFICATION: BIT_CORE_TRACE(message); return;
        }

        BIT_CORE_ASSERT(false, "Unknown severity level!");
    }

    void GraphicsAPI::Init()
    {
    BIT_CORE_ASSERT( gladLoadGL() , "GLAD could not init!" );

    #ifdef BIT_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLLogMessage, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
    #endif

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        BIT_CORE_INFO("OpenGL Info:");
        BIT_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        BIT_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        BIT_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

    }

    void GraphicsAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void GraphicsAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void GraphicsAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    uint32_t GraphicsAPI::GetTextureSlots()
    {
        int texture_units;
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &texture_units);
        return texture_units;
    }

    void GraphicsAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}