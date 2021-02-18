#include "bitpch.h"

#include "Graphics/API/Buffer.h"

#include "glad/glad.h"

namespace Bit {
    
    static uint32_t BufferTypeToGL(BufferType type)
    {
        switch (type)
        {
            case BufferType::Stream_Draw:  return GL_STREAM_DRAW;
            case BufferType::Stream_Read:  return GL_STREAM_READ;
            case BufferType::Stream_Copy:  return GL_STREAM_COPY;
            case BufferType::Static_Draw:  return GL_STATIC_DRAW;
            case BufferType::Static_Read:  return GL_STATIC_READ;
            case BufferType::Static_Copy:  return GL_STATIC_COPY;
            case BufferType::Dynamic_Draw: return GL_DYNAMIC_DRAW;
            case BufferType::Dynamic_Read: return GL_DYNAMIC_READ;
            case BufferType::Dynamic_Copy: return GL_DYNAMIC_COPY;
        }

        BIT_CORE_ASSERT(false, "Unknown Vertex Buffer Type!");
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////
    // VertexBuffer /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size, const BufferType& type)
    {
        return std::make_shared<VertexBuffer>(vertices, size, type);
    }

    VertexBuffer::VertexBuffer(float* vertices, uint32_t size, const BufferType& type)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, BufferTypeToGL(type));
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(const uint32_t& offset, const void* vertices, const uint32_t& size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
    }


    /////////////////////////////////////////////////////////////////////////////
    // IndexBuffer //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size, const BufferType& type)
    {
        return std::make_shared<IndexBuffer>(indices, size, type);
    }

    IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count, const BufferType& type)
        : m_Count(count)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, BufferTypeToGL(type));
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::SetData(const uint32_t& offset, const void* indices, const uint32_t& size)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indices);
    }

}