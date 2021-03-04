#pragma once
#include "Core/Base.h"

#include "Core/Timestep.h"

#include "Graphics/Camera.h"

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

        void OnUpdate(Timestep& ts); //TODO: RENDERING WITH MULTIPLE PIPELINES!!!!!!!

        void SetCamera(Ref<Camera> camera) { m_Camera = camera; }
    
        void OnStartRuntime();
        void OnEndRuntime();
        void OnUpdateRuntime();

    private:
        entt::registry m_Registry;

        Ref<Camera> m_Camera;

        friend class Entity;
    };

}