#include "bitpch.h"

#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "ECS/Components.h"

#include "Graphics/SpriteRenderer.h"
#include "Graphics/PrimitiveRenderer.h"

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

    void Scene::OnUpdate(Timestep& ts)
    {
        auto& camera = m_Camera; //TODO: FIX SORTING

        /*
         *    SCRIPTING
         */

        {
            m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
                {
                    if (!nsc.Instance)
                    {
                        nsc.Instance = nsc.InstantiateScript();
                        nsc.Instance->m_Entity = Entity{ entity, this };
                        nsc.Instance->OnCreate();
                    }

                    nsc.Instance->OnUpdate(ts);
                });
        }

        /*
         *    RENDERING
         */

        {
            SpriteRenderer::BeginScene(camera->Get());

            auto group = m_Registry.group<SpriteComponent>(entt::get<TransformComponent>);

            group.sort<TransformComponent>([camera](const auto& lhs, const auto& rhs) {
                float leftLength = glm::dot(lhs.Position - camera->GetPosition(), camera->GetForwardDirection());
                float rightLength = glm::dot(rhs.Position - camera->GetPosition(), camera->GetForwardDirection());
                return leftLength > rightLength; //TODO: FIX THIS
            });

            group.each([](auto entity, auto& sprite, auto& transform) 
                {
                    if (sprite.Texture == nullptr) SpriteRenderer::DrawQuad(transform.GetTransform(), sprite.Color);
                    else SpriteRenderer::DrawQuad(transform.GetTransform(), sprite.Texture, 1.0f, sprite.Color);
                });

            SpriteRenderer::EndScene();
        }

        {
            PrimitiveRenderer::BeginScene(camera->Get());

            auto group = m_Registry.group<PrimitiveComponent>(entt::get<TransformComponent>);
            group.each([](auto entity, auto& primitive, auto& transform)
                {
                    if (primitive.IsVisible)
                    {
                        PrimitiveRenderer::GetShader()->UploadUniformMat4("u_Transform", transform.GetTransform());
                        PrimitiveRenderer::Draw(primitive.Type, primitive.Points, primitive.Index, primitive.Color);
                    }
                });
            
            PrimitiveRenderer::EndScene();
        }

    }

}
