#pragma once
#include "Core/Base.h"
#include "ECS/Scene.h"
#include "entt.hpp"

namespace Bit {

    class Entity
    {
    public:
        Entity() = default;
        Entity(const Entity& other) = default;
        Entity(entt::entity handle, Scene* scene)
            : m_EntityHandle(handle), m_Scene(scene)
        {}

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            if(HasComponent<T>())
            {
                BIT_CORE_ERROR("Entity already has component!");
                return GetComponent<T>();
            }
            T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            return component;
        }

        template<typename T>
        T& GetComponent()
        {
            BIT_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Scene->m_Registry.has<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveComponent()
        {
            BIT_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
            m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        operator bool() const { return m_EntityHandle != entt::null; }
        operator entt::entity() const { return m_EntityHandle; }
        operator uint32_t() const { return (uint32_t)m_EntityHandle; }

        bool operator==(const Entity& other) const
        {
            return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
        }

        bool operator!=(const Entity& other) const
        {
            return !(*this == other);
        }
    private:
        entt::entity m_EntityHandle{ entt::null };
        Scene* m_Scene = nullptr;
    };


}