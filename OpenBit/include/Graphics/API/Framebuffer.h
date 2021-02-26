#pragma once
#include "Core/Base.h"

#include "Graphics/API/Texture.h"

#include <glm/glm.hpp>

namespace Bit {

    enum class Attachment
    {
        Depth = 0, Stencil, Depth_Stencil, Color
    };
    
    class Framebuffer
    {
    public:
        static Ref<Framebuffer> Create(Attachment type, const uint32_t& width, const uint32_t& height);
        Framebuffer(Attachment type, const uint32_t& width, const uint32_t& height);
        ~Framebuffer();
    
        void SetAttachment(Attachment type);
        void ResizeTex(const uint32_t& width, const uint32_t& height);

        void ToScreen();

        void Bind() const;
        void Unbind() const;
    
        bool IsComplete() const;
    
    private:
        uint32_t m_RendererID;

        Attachment m_Type;
        uint32_t m_AttachementID;
        uint32_t m_Width, m_Height;
    };
    
}