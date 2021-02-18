#include "bitpch.h"

#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "ECS/Components.h"

#include "Graphics/SpriteRenderer.h"

#include <entt.hpp>

namespace Bit {

    Scene::Scene()
    {

    }

    Scene::~Scene()
    {

    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;
        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

    void Scene::OnRender()
    {
        auto camera = *m_Camera;
        SpriteRenderer::BeginScene(camera);
        auto group = m_Registry.group<SpriteComponent>(entt::get<TransformComponent>);
        group.sort<TransformComponent>([&camera](const auto& lhs, const auto& rhs) {
            float leftLength = glm::dot(lhs.Position - camera.GetPosition(), camera.GetForwardDirection());
            float rightLength = glm::dot(rhs.Position - camera.GetPosition(), camera.GetForwardDirection());
            return leftLength > rightLength;
        });

        for(auto entity : group)
        {
            auto& transform = group.get<TransformComponent>(entity);
            auto& sprite = group.get<SpriteComponent>(entity);
            if(sprite.Texture==nullptr) SpriteRenderer::DrawQuad(transform.GetTransform(), sprite.Color);
            else SpriteRenderer::DrawQuad( transform.GetTransform(), sprite.Texture, 1.0f, sprite.Color);
        }

        SpriteRenderer::EndScene();
    }

    void Scene::OnUpdate(Timestep ts)
    {
 
    }

}
