#pragma once

#include "ECS/Entity.h"

namespace Bit {

    class ScriptableEntity
    {
    public:
        template<typename T>
        T& GetComponent()
        {
            return m_Entity.GetComponent<T>();
        }
    protected:
        virtual void OnCreate() {}
        virtual void OnDestroy() {}
        virtual void OnUpdate(Timestep) {}

    private:
        Entity m_Entity;
        friend class Scene;
    };

}
