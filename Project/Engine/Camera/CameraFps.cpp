#include "CameraFps.hpp"
#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


CameraFps::CameraFps(const glm::vec3 &pos)
	: Camera(pos)
{

}

CameraFps::CameraFps(const glm::vec3 &pos, int screenWidth, int screenHeight)
	: Camera(pos, screenWidth, screenHeight)
{
}

CameraFps::~CameraFps()
{

}

glm::mat4 CameraFps::viewMatrix() const
{
	return glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

glm::mat4 CameraFps::projectionMatrix() const
{
	return glm::perspective(_fov, (GLfloat)_screenWidth / (GLfloat)_screenHeight, 0.1f, 100.0f);
}
#include <iostream>

void CameraFps::updateDirection(float xOffset, float yOffset, float)
{
	float sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;
	
	_yaw += xOffset;
	_pitch += yOffset;
	_xOffset = xOffset;
	_yOffset = yOffset;
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_cameraFront = glm::normalize(front);
	
}