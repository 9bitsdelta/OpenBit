#include "bitpch.h"
#include "Graphics/API/Texture.h"
#include "stb_image.h"

#include "glad/glad.h"

namespace Bit {
    
    ///////////////////////////////////////////////////////////////////////////////
    // Texture2D //////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    
    Ref<Texture2D> Texture2D::Create(const uint32_t& width, const uint32_t& height)
    {
        return std::make_shared<Texture2D>(width, height);
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        return std::make_shared<Texture2D>(path);
    }

    Texture2D::Texture2D(const uint32_t& width, const uint32_t& height)
        : m_Width(width), m_Height(height)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    Texture2D::Texture2D(const std::string& path)
        :m_RendererID(0), m_Path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        BIT_CORE_ASSERT(data, "Failed to load image: {} !", path.c_str());
        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        BIT_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, width, height);
        
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTextureSubImage2D(m_RendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    
    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }
    
    void Texture2D::SetData(void* data, uint32_t size)
    {
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        BIT_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void Texture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }

}