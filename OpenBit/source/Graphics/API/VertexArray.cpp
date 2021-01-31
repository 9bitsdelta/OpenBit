#include "Graphics/API/VertexArray.h"

namespace Bit {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case Bit::ShaderDataType::Float:    return GL_FLOAT;
            case Bit::ShaderDataType::Float2:   return GL_FLOAT;
            case Bit::ShaderDataType::Float3:   return GL_FLOAT;
            case Bit::ShaderDataType::Float4:   return GL_FLOAT;
            case Bit::ShaderDataType::Mat3:     return GL_FLOAT;
            case Bit::ShaderDataType::Mat4:     return GL_FLOAT;
            case Bit::ShaderDataType::Int:      return GL_INT;
            case Bit::ShaderDataType::Int2:     return GL_INT;
            case Bit::ShaderDataType::Int3:     return GL_INT;
            case Bit::ShaderDataType::Int4:     return GL_INT;
            case Bit::ShaderDataType::Bool:     return GL_BOOL;
        }

        BIT_CORE_ASSERT(false, "Unknown Shader Data Type!");
        return 0;
    }

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        BIT_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }

        m_VertexBuffer = vertexBuffer;
    }

    void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

}