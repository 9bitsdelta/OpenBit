#include "bitpch.h"
#include "Graphics/API/Framebuffer.h"

#include "glad/glad.h"

#include "Core/Application.h"

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

    Ref<Framebuffer> Framebuffer::Create(Attachment type, const uint32_t& width, const uint32_t& height)
    {
        return std::make_shared<Framebuffer>(type, width, height);
    }

    Framebuffer::Framebuffer(Attachment type, const uint32_t& width, const uint32_t& height)
        : m_Type(type), m_Width(width), m_Height(height)
    {
        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_AttachementID);
        glBindTexture(GL_TEXTURE_2D, m_AttachementID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glFramebufferTexture2D(GL_FRAMEBUFFER, AttachmentTypeToGL(type), GL_TEXTURE_2D, m_AttachementID, 0);
    }
    
    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(1, &m_AttachementID);
    }
    
    void Framebuffer::SetAttachment(Attachment type)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glDeleteTextures(1, &m_AttachementID);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_AttachementID);
        glBindTexture(GL_TEXTURE_2D, m_AttachementID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, AttachmentTypeToGL(type), GL_TEXTURE_2D, m_AttachementID, 0);
    }
    
    void Framebuffer::ResizeTex(const uint32_t& width, const uint32_t& height)
    {
        m_Width = width; m_Height = height;
        glBindTexture(GL_TEXTURE_2D, m_AttachementID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    }

    void Framebuffer::ToScreen()
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_RendererID);
        glReadBuffer(AttachmentTypeToGL(m_Type));
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        auto height = Application::Get().GetWindow().GetHeight();
        auto width = Application::Get().GetWindow().GetWidth();
        glViewport(0, 0, width, height);

        glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, width, height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    }

    bool Framebuffer::IsComplete() const
    {
        return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    }
    
    void Framebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Width, m_Height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Framebuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        auto height = Application::Get().GetWindow().GetHeight();
        auto width = Application::Get().GetWindow().GetWidth();
        glViewport(0, 0, width, height);
    }

}