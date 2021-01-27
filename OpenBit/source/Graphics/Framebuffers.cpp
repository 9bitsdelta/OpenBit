#include "Graphics/Framebuffers.h"

namespace Bit {
	
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
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
	
	void FramebufferTexture::ResizeTexture(uint32_t width, uint32_t height)
	{
		m_Width = width; m_Height = height;
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}
	
	FrameBuffer::FrameBuffer(GLenum target)
		:m_RendererID(0), m_Target(target)
	{
		glCreateFramebuffers(1, &m_RendererID);
	}
	
	Ref<FrameBuffer> FrameBuffer::Create(GLenum target)
	{
		return std::make_shared<FrameBuffer>(target);
	}
	
	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}
	
	void FrameBuffer::Bind() const
	{
		glBindFramebuffer(m_Target, m_RendererID);
	}
	
	void FrameBuffer::Unbind() const
	{
		glBindFramebuffer(m_Target, 0);
	}
	
	void FrameBuffer::AttachTexture(const Ref<FramebufferTexture>& texture, GLenum attachement)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachement, GL_TEXTURE_2D, texture->GetInternalID(), 0);
	}
	
	void FrameBuffer::CheckStatus(const GLenum& target)
	{
		if (glCheckFramebufferStatus(target) != GL_FRAMEBUFFER_COMPLETE) { BIT_CORE_ERROR("Framebuffer is incomplete"); }
		else { BIT_CORE_WARN("Framebuffer complete"); }
	}
	
}