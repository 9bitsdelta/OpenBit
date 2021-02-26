#include "bitpch.h"
#include "Graphics/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Bit {

    Ref<Camera> Camera::Create(Projection type)
    {
        return std::make_shared<Camera>(type);
    }

    Camera::Camera(Projection type)
        :m_Type(type)
    {
        UpdateViewProjection();
    }

    void Camera::SetOrthographicProjection(float left, float right, float bottom, float top)
    {
        m_OrthographicProjection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        UpdateViewProjection();
    }

    void Camera::SetPerspectiveProjection(float verticalFov, float aspectRatio, float zNear, float zFar)
    {
        m_PerspectiveProjection = glm::perspective(verticalFov, aspectRatio, zNear, zFar);
        UpdateViewProjection();
    }

    void Camera::UpdateView()
    {
        glm::quat orientation = GetOrientation();

        m_View = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
        m_View = glm::inverse(m_View);
        UpdateViewProjection();
    }

    void Camera::UpdateViewProjection()
    {
        switch(m_Type)
        {
        case Projection::Null:         m_ViewProjection = m_View; return;
        case Projection::Orthographic: m_ViewProjection = m_OrthographicProjection * m_View; return;
        case Projection::Perspective:  m_ViewProjection = m_PerspectiveProjection * m_View; return;
        }
    }

	glm::vec3 Camera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 Camera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 Camera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat Camera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, -m_Roll));
	}
}