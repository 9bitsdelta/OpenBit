#pragma once

#include "Core/Base.h"
#include <string>

#include "glad/glad.h"

namespace Bit {
    
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual bool operator==(const Texture& other) const = 0;

    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const uint32_t& width, const uint32_t& height);
        static Ref<Texture2D> Create(const std::string& path);

        Texture2D(const uint32_t& width, const uint32_t& height);
        Texture2D(const std::string& path);
        virtual ~Texture2D();

        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }

        virtual void SetData(void* data, uint32_t size) override;

        virtual void Bind(uint32_t slot = 0) const override;

        virtual bool operator==(const Texture& other) const override
        {
            return m_RendererID == ((Texture2D&)other).m_RendererID;
        }

    protected:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;

    };
    
}