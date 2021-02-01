#include "bitpch.h"

#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "ECS/Components.h"

#include "Graphics/Batch2DRenderer.h"

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

    void Scene::OnRender(const glm::mat4& camera)
    {
        Renderer2D::BeginScene(camera);

        auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
        for(auto entity : view)
        {
            auto& transform = view.get<TransformComponent>(entity);
            auto& sprite = view.get<SpriteRendererComponent>(entity);
            Renderer2D::DrawQuad( transform.GetTransform() , sprite.Texture );
        }

        Renderer2D::EndScene();
    }

    void Scene::OnUpdate(Timestep ts)
    {

    }

}