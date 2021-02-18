#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Graphics/API/GraphicsAPI.h"

namespace Bit {

    struct TagComponent
    {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
            :Tag(tag) {}
    };

    struct TransformComponent
    {
        glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale    = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;

        glm::mat4 GetTransform() const
        {
            return glm::translate(glm::mat4(1.0f), Position)
                 * glm::toMat4(glm::quat(Rotation))
                 * glm::scale(glm::mat4(1.0f), Scale);
        }

    };

    struct SpriteComponent
    {
        //bool IsVisible = true;
        Ref<Texture2D> Texture = nullptr;
        glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(const Ref<Texture2D>& tex)
            :Texture(tex) {}
        SpriteComponent(const glm::vec4& color)
            :Color(color) {}
        SpriteComponent(const Ref<Texture2D>& tex, const glm::vec4& color)
            :Texture(tex), Color(color) {}
    };

    struct PrimitiveComponent
    {

    };

}