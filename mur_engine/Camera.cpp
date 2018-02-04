#include "stdafx.h"
#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float fovy)
{
	m_Pos = pos;
	m_Up = up;
	m_Yaw = yaw;
	m_Pitch = pitch;
	m_Fovy = fovy;
	UpdateCameraVector();
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
}

glm::vec3 Camera::GetPos()
{
	return m_Pos;
}

float Camera::GetFovy()
{
	return m_Fovy;
}

void Camera::UpdateCameraVector()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);
}
