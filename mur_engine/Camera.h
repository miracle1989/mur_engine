#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "GLM/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float FOVY = 90.0f;

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0), glm::vec3 up = glm::vec3(0.0, 1.0, 0.0), float yaw = YAW, float pitch = PITCH, float fovy = FOVY);
	
	~Camera();

	glm::mat4 GetViewMatrix();

	glm::vec3 GetPos();

	float GetFovy();


private:
	glm::vec3 m_Pos;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	
	float m_Yaw;
	float m_Pitch;

	float m_Fovy;

	void UpdateCameraVector();
};


#endif // !_CAMERA_H_