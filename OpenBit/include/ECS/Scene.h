#pragma once
#include "Core/Base.h"

#include "Core/Timestep.h"

#include <entt.hpp>
#include <glm/glm.hpp>

namespace Bit {

    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = std::string());
        void DestroyEntity(Entity entity);

        void OnRender(const glm::mat4& camera); //TODO: OnRender should be able to use different pipelines
        void OnUpdate(Timestep ts);

    public:
        entt::registry m_Registry;
        //TODO: Bind a scene camera;

        friend class Entity;
    };

}