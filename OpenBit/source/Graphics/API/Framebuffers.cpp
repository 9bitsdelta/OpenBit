#include "bitpch.h"
#include "Graphics/API/Framebuffers.h"

#include "glad/glad.h"

namespace Bit {
    
    uint32_t AttachmentTypeToGL(Attachment type)
    {
        switch(type)
        {
        case Attachment::Depth:          return GL_DEPTH_ATTACHMENT;
        case Attachment::Stencil:        return GL_STENCIL_ATTACHMENT;
        case Attachment::Depth_Stencil:  return GL_DEPTH_STENCIL_ATTACHMENT;
        case Attachment::Color:          return GL_COLOR_ATTACHMENT0;
        }
        
        BIT_CORE_ASSERT(false, "Unknown Framebuffer Attachement Type");
        return 0;
    }

    Ref<FramebufferTexture> FramebufferTexture::Create(const uint32_t& width, const uint32_t& height)
    {
        return std::make_shared<FramebufferTexture>(width, height);
    }
    
    FramebufferTexture::FramebufferTexture(const uint32_t& width, const uint32_t& height)
        :m_RendererID(0), m_Width(width), m_Height(height)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        Bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        Unbind();
    }
    
    FramebufferTexture::~FramebufferTexture()
    {
        glDeleteTextures(1, &m_RendererID);
    }
    
    void FramebufferTexture::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }
    
    void FramebufferTexture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void FramebufferTexture::ResizeTexture(const uint32_t& width, const uint32_t& height)
    {
        m_Width = width; m_Height = height;
        Bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    }
    
    FrameBuffer::FrameBuffer()
        :m_RendererID(0)
    {
        glCreateFramebuffers(1, &m_RendererID);
    }
    
    Ref<FrameBuffer> FrameBuffer::Create()
    {
        return std::make_shared<FrameBuffer>();
    }
    
    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
    }
    
    void FrameBuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }
    
    void FrameBuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void FrameBuffer::AttachTexture(const Ref<FramebufferTexture>& texture, Attachment type)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, AttachmentTypeToGL(type), GL_TEXTURE_2D, texture->GetInternalID(), 0);
    }
    
    void FrameBuffer::CheckStatus() const
    {
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { BIT_CORE_ERROR("Framebuffer is incomplete"); }
        else { BIT_CORE_WARN("Framebuffer complete"); }
    }
    
}