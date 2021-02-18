#pragma once
#include "Core/Base.h"

namespace Bit {

    enum class Attachment
    {
        Depth = 0, Stencil, Depth_Stencil, Color
    };

    class FramebufferTexture
    {
    public:
        static Ref<FramebufferTexture> Create(const uint32_t& width, const uint32_t& height);
        FramebufferTexture(const uint32_t& width, const uint32_t& height);
        ~FramebufferTexture();
    
        void ResizeTexture(const uint32_t& width, const uint32_t& height);
    
        uint32_t GetInternalID() const { return m_RendererID; }
        void Bind() const;
        void Unbind() const;
    
    private:
        uint32_t m_RendererID;
        uint32_t m_Width, m_Height;
    };
    
    class FrameBuffer
    {
    public:
        static Ref<FrameBuffer> Create();
        FrameBuffer();
        ~FrameBuffer();
    
        void AttachTexture(const Ref<FramebufferTexture>& texture, Attachment type);
        
        void Bind() const;
        void Unbind() const;
    
        void CheckStatus() const;
        uint32_t GetInternalID() const { return m_RendererID; }
    
    private:
        uint32_t m_RendererID;
    };
    
}