#pragma once
#include "Core/Base.h"

#include <glm/glm.hpp>

namespace Bit {

    enum class Projection
    {
        Null = 0, Perspective, Orthographic
    };

    class Camera
    {
    public:
        static Ref<Camera> Create(Projection type);
        Camera(Projection type);

        void SetType(Projection type) { m_Type = type; UpdateViewProjection(); }
        void SetPosition(const glm::vec3& position) { m_Position = position; UpdateView(); }
        void SetRotation(float pitch, float yaw, float roll) { m_Pitch = pitch, m_Yaw = yaw; m_Roll = roll; UpdateView(); }

        void SetPerspectiveProjection(float verticalFov, float aspectRatio, float zNear, float zFar);
        void SetOrthographicProjection(float left, float right, float bottom, float top);

        Projection GetType() const { return m_Type; }
        glm::vec3 GetPosition() const { return m_Position; }
        float GetPitch() const { return m_Pitch; }
        float GetYaw() const { return m_Yaw; }

        glm::mat4 Get() const { return m_ViewProjection; }
    
        glm::vec3 GetUpDirection() const;
        glm::vec3 GetRightDirection() const;
        glm::vec3 GetForwardDirection() const;
    
    private:
        void UpdateView();
        void UpdateViewProjection();

        glm::quat GetOrientation() const;

    private:
        Projection m_Type;

        glm::mat4 m_View = glm::mat4(1.0f);

        glm::mat4 m_OrthographicProjection = glm::mat4(1.0f);
        glm::mat4 m_PerspectiveProjection = glm::mat4(1.0f);
        
        glm::mat4 m_ViewProjection = glm::mat4(1.0f);

        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Pitch = 0.0f, m_Yaw = 0.0f, m_Roll = 0.0f;
    };

}