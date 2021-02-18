#include "bitpch.h"
#include "Graphics/API/GraphicsAPI.h"

#include "glad/glad.h"

#include "Core/Log.h"

namespace Bit {

    static uint32_t DrawMethodToGL(DrawMethod type)
    {
        switch(type)
        {
        case DrawMethod::Points:          return GL_POINTS;
        case DrawMethod::Lines:           return GL_LINES;
        case DrawMethod::Line_Strip:      return GL_LINE_STRIP;
        case DrawMethod::Line_Loop:       return GL_LINE_LOOP;
        case DrawMethod::Triangles:       return GL_TRIANGLES;
        case DrawMethod::Triangle_Strip:  return GL_TRIANGLE_STRIP;
        case DrawMethod::Triangle_Fan:    return GL_TRIANGLE_FAN;
        }

        BIT_CORE_ASSERT(false, "Unknown Draw Method");
        return 0;
    }

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

    void GraphicsAPI::DrawIndexed(DrawMethod type, const Ref<VertexArray>& vertexArray, uint32_t indexCount)
    {
        vertexArray->Bind();
        uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(DrawMethodToGL(type), count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
        vertexArray->Unbind();
    }

}