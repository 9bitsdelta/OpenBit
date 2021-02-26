#include "bitpch.h"

#include "Graphics/SpriteRenderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#define MAX_QUADS    20000
#define MAX_VERTICES 4*MAX_QUADS
#define MAX_INDICES  6*MAX_QUADS
#define MAX_TEXTURE_SLOTS 32 //TODO: RenderCap

namespace Bit {
    
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex;
        float TilingFactor;
    };
    
    struct SpriteRendererData
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;
    
        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;
    
        std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> TextureSlots;
        uint32_t TextureSlotIndex = 1; // 0 = white texture
    
        glm::vec4 QuadVertexPositions[4];
    
        SpriteRenderer::Statistics Stats;
    };
    
    static SpriteRendererData s_Data;
    
    void SpriteRenderer::Init()
    {
        s_Data.QuadVertexArray = VertexArray::Create();
    
        s_Data.QuadVertexBuffer = VertexBuffer::Create(nullptr, MAX_VERTICES * sizeof(QuadVertex), BufferType::Dynamic_Draw);
        s_Data.QuadVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoord" },
            { ShaderDataType::Float, "a_TexIndex" },
            { ShaderDataType::Float, "a_TilingFactor" }
        });
        s_Data.QuadVertexArray->SetVertexBuffer(s_Data.QuadVertexBuffer);
    
        s_Data.QuadVertexBufferBase = new QuadVertex[MAX_VERTICES];
    
        uint32_t* quadIndices = new uint32_t[MAX_INDICES];
    
        uint32_t offset = 0;
        for (uint32_t i = 0; i < MAX_INDICES; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;
    
            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;
    
            offset += 4;
        }
    
        Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, MAX_INDICES);
        s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
        delete[] quadIndices;
    
        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    
        int32_t samplers[MAX_TEXTURE_SLOTS];
        for (uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++)
            samplers[i] = i;
    
        const std::string shaderVertSrc = R"(
        #version 450
        
        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;
        layout(location = 2) in vec2 a_TexCoord;
        layout(location = 3) in float a_TexIndex;
        layout(location = 4) in float a_TilingFactor;
        
        uniform mat4 u_ViewProjection;
        
        out vec4 v_Color;
        out vec2 v_TexCoord;
        out flat float v_TexIndex;
        out float v_TilingFactor;
        
        void main()
        {
            v_Color = a_Color;
            v_TexCoord = a_TexCoord;
            v_TexIndex = a_TexIndex;
            v_TilingFactor = a_TilingFactor;
            gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
        })";

        const std::string shaderFragSrc = R"(
            #version 450

            layout(location = 0) out vec4 color;

            in vec4 v_Color;
            in vec2 v_TexCoord;
            in flat float v_TexIndex;
            in float v_TilingFactor;

            uniform sampler2D u_Textures[32];

            void main()
            {
                vec4 texColor = v_Color;
                switch (int(v_TexIndex))
                {
                case 0: texColor *= texture(u_Textures[0], v_TexCoord * v_TilingFactor); break;
                case 1: texColor *= texture(u_Textures[1], v_TexCoord * v_TilingFactor); break;
                case 2: texColor *= texture(u_Textures[2], v_TexCoord * v_TilingFactor); break;
                case 3: texColor *= texture(u_Textures[3], v_TexCoord * v_TilingFactor); break;
                case 4: texColor *= texture(u_Textures[4], v_TexCoord * v_TilingFactor); break;
                case 5: texColor *= texture(u_Textures[5], v_TexCoord * v_TilingFactor); break;
                case 6: texColor *= texture(u_Textures[6], v_TexCoord * v_TilingFactor); break;
                case 7: texColor *= texture(u_Textures[7], v_TexCoord * v_TilingFactor); break;
                case 8: texColor *= texture(u_Textures[8], v_TexCoord * v_TilingFactor); break;
                case 9: texColor *= texture(u_Textures[9], v_TexCoord * v_TilingFactor); break;
                case 10: texColor *= texture(u_Textures[10], v_TexCoord * v_TilingFactor); break;
                case 11: texColor *= texture(u_Textures[11], v_TexCoord * v_TilingFactor); break;
                case 12: texColor *= texture(u_Textures[12], v_TexCoord * v_TilingFactor); break;
                case 13: texColor *= texture(u_Textures[13], v_TexCoord * v_TilingFactor); break;
                case 14: texColor *= texture(u_Textures[14], v_TexCoord * v_TilingFactor); break;
                case 15: texColor *= texture(u_Textures[15], v_TexCoord * v_TilingFactor); break;
                case 16: texColor *= texture(u_Textures[16], v_TexCoord * v_TilingFactor); break;
                case 17: texColor *= texture(u_Textures[17], v_TexCoord * v_TilingFactor); break;
                case 18: texColor *= texture(u_Textures[18], v_TexCoord * v_TilingFactor); break;
                case 19: texColor *= texture(u_Textures[19], v_TexCoord * v_TilingFactor); break;
                case 20: texColor *= texture(u_Textures[20], v_TexCoord * v_TilingFactor); break;
                case 21: texColor *= texture(u_Textures[21], v_TexCoord * v_TilingFactor); break;
                case 22: texColor *= texture(u_Textures[22], v_TexCoord * v_TilingFactor); break;
                case 23: texColor *= texture(u_Textures[23], v_TexCoord * v_TilingFactor); break;
                case 24: texColor *= texture(u_Textures[24], v_TexCoord * v_TilingFactor); break;
                case 25: texColor *= texture(u_Textures[25], v_TexCoord * v_TilingFactor); break;
                case 26: texColor *= texture(u_Textures[26], v_TexCoord * v_TilingFactor); break;
                case 27: texColor *= texture(u_Textures[27], v_TexCoord * v_TilingFactor); break;
                case 28: texColor *= texture(u_Textures[28], v_TexCoord * v_TilingFactor); break;
                case 29: texColor *= texture(u_Textures[29], v_TexCoord * v_TilingFactor); break;
                case 30: texColor *= texture(u_Textures[30], v_TexCoord * v_TilingFactor); break;
                case 31: texColor *= texture(u_Textures[31], v_TexCoord * v_TilingFactor); break;
                }
                color = texColor;
            })";

        s_Data.TextureShader = Shader::Create("SpriteShader", shaderVertSrc, shaderFragSrc);
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->UploadUniformIntArray("u_Textures", samplers, MAX_TEXTURE_SLOTS);
    
        // Set first texture slot to 0
        s_Data.TextureSlots[0] = s_Data.WhiteTexture;
    
        s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }
    
    void SpriteRenderer::Shutdown()
    {
        delete[] s_Data.QuadVertexBufferBase;
        s_Data.~SpriteRendererData();
    }
    
    void SpriteRenderer::BeginScene(const glm::mat4& camera)
    {
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->UploadUniformMat4("u_ViewProjection", camera);
        
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthFunc(GL_LEQUAL);
        
        StartBatch();
    }
    
    void SpriteRenderer::EndScene()
    {
        Flush();

        glDisable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
    }
    
    void SpriteRenderer::StartBatch()
    {
        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    
        s_Data.TextureSlotIndex = 1;
    }
    
    void SpriteRenderer::Flush()
    {
        if (s_Data.QuadIndexCount == 0)
            return; // Nothing to draw
    
        uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
        s_Data.QuadVertexBuffer->SetData(0, s_Data.QuadVertexBufferBase, dataSize);
    
        // Bind textures
        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
            s_Data.TextureSlots[i]->Bind(i);
    
        GraphicsAPI::DrawIndexed(DrawMethod::Triangles, s_Data.QuadVertexArray, s_Data.QuadIndexCount);
        s_Data.Stats.DrawCalls++;
    }
    
    void SpriteRenderer::NextBatch()
    {
        Flush();
        StartBatch();
    }
    
    void SpriteRenderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }
    
    void SpriteRenderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    
        DrawQuad(transform, color);
    }
    
    void SpriteRenderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
    }
    
    void SpriteRenderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    
        DrawQuad(transform, texture, tilingFactor, tintColor);
    }
    
    void SpriteRenderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        constexpr size_t quadVertexCount = 4;
        const float textureIndex = 0.0f; // White Texture
        constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        const float tilingFactor = 1.0f;
    
        if (s_Data.QuadIndexCount >= MAX_INDICES)
            NextBatch();
    
        for (size_t i = 0; i < quadVertexCount; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }
    
        s_Data.QuadIndexCount += 6;
    
        s_Data.Stats.QuadCount++;
    }
    
    void SpriteRenderer::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        constexpr size_t quadVertexCount = 4;
        constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    
        if (s_Data.QuadIndexCount >= MAX_INDICES)
            NextBatch();
    
        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
        {
            if (*s_Data.TextureSlots[i] == *texture)
            {
                textureIndex = (float)i;
                break;
            }
        }
    
        if (textureIndex == 0.0f)
        {
            if (s_Data.TextureSlotIndex >= MAX_TEXTURE_SLOTS)
                NextBatch();
    
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }
    
        for (size_t i = 0; i < quadVertexCount; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = tintColor;
            s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }
    
        s_Data.QuadIndexCount += 6;
    
        s_Data.Stats.QuadCount++;
    }
    
    void SpriteRenderer::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }
    
    void SpriteRenderer::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    
        DrawQuad(transform, color);
    }
    
    void SpriteRenderer::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
    }
    
    void SpriteRenderer::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    
        DrawQuad(transform, texture, tilingFactor, tintColor);
    }
    
    void SpriteRenderer::ResetStats()
    {
        memset(&s_Data.Stats, 0, sizeof(Statistics));
    }
    
    SpriteRenderer::Statistics SpriteRenderer::GetStats()
    {
        return s_Data.Stats;
    }
}