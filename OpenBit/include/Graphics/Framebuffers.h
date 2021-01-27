#pragma once
#include <GL/glew.h>

#include "Core/Base.h"

namespace Bit {
	
	class FramebufferTexture
	{
	public:
		static Ref<FramebufferTexture> Create(const uint32_t& width, const uint32_t& height);
		FramebufferTexture(const uint32_t& width, const uint32_t& height);
	
		~FramebufferTexture();
	
		void Bind() const;
		void Unbind() const;
	
		void ResizeTexture(uint32_t width, uint32_t height);
	
		uint32_t GetInternalID() const { return m_RendererID; }
	
	private:
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
	};
	
	class FrameBuffer
	{
	public:
		FrameBuffer(GLenum target = GL_FRAMEBUFFER);
		static Ref<FrameBuffer> Create(GLenum target = GL_FRAMEBUFFER);
	
		~FrameBuffer();
	
		void Bind() const;
		void Unbind() const;
	
		void AttachTexture(const Ref<FramebufferTexture>& texture, GLenum attachement = GL_COLOR_ATTACHMENT0);
	
		static void CheckStatus(const GLenum& target);
	private:
		uint32_t m_RendererID;
		GLenum m_Target;
	};
	
}