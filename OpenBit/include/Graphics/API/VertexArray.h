#pragma once

#include "Core/Base.h"
#include "Graphics/API/Buffer.h"

namespace Bit {

    class VertexArray
    {
    public:
        static Ref<VertexArray> Create();
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

        const Ref<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
        const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
    };

}
