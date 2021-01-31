#pragma once

#include "Graphics/API/VertexArray.h"
#include "Graphics/API/Texture.h"
#include "Graphics/API/Shader.h"
#include "Graphics/API/Framebuffers.h"

namespace Bit {

    class GraphicsAPI
    {
    public:
        static void Init();
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        static void SetClearColor(const glm::vec4& color);
        static void Clear();

        static uint32_t GetTextureSlots();

        static void DrawIndexed(const Ref<VertexArray>& vertexArray);
    };

}