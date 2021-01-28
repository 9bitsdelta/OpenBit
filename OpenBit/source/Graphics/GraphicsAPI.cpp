#include "Graphics/GraphicsAPI.h"

#include <GL/glew.h>

#include "Core/Log.h"

namespace Bit {

    static DebugLogLevel s_DebugLogLevel = DebugLogLevel::HighAssert;

    void SetGLDebugLogLevel(DebugLogLevel level)
    {
        s_DebugLogLevel = level;
    }

    void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            if ((int)s_DebugLogLevel > 0)
            {
                BIT_CORE_ERROR("[OpenGL Debug HIGH] {0}", message);
                if (s_DebugLogLevel == DebugLogLevel::HighAssert)
                    BIT_CORE_ASSERT(false, "GL_DEBUG_SEVERITY_HIGH");
            }
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            if ((int)s_DebugLogLevel > 2)
                BIT_CORE_WARN("[OpenGL Debug MEDIUM] {0}", message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            if ((int)s_DebugLogLevel > 3)
                BIT_CORE_INFO("[OpenGL Debug LOW] {0}", message);
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            if ((int)s_DebugLogLevel > 4)
                BIT_CORE_TRACE("[OpenGL Debug NOTIFICATION] {0}", message);
            break;
        }
    }

    void EnableGLDebugging()
    {
        glDebugMessageCallback(OpenGLLogMessage, nullptr);
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    }

    void GraphicsAPI::Init()
    {
        EnableGLDebugging();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

    const uint32_t& GraphicsAPI::GetTextureSlots()
    {
        GLint texture_units;
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &texture_units);
        return texture_units;
    }


    void GraphicsAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}