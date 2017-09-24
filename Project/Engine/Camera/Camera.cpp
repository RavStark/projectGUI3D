#include "Camera.hpp"
#include "GL\glew.h"
#include <iostream>

Camera::Camera(const glm::vec3 &pos)
	: _cameraPos(pos)
{
//	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	//std::cout << cameraDirection.x << " " << cameraDirection.y << " " << cameraDirection.z << std::endl;
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

}

Camera::Camera(const glm::vec3 &pos, int screenWidth, int screenHeight)
	: _cameraPos(pos), _screenWidth(screenWidth), _screenHeight(screenHeight)
{
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	
	//glm::vec3 cameraRight = glm::normalize(glm::cross(_cameraUp, cameraDirection));
	//std::cout << cameraRight.x << " " << cameraRight.y << " " << cameraRight.z << std::endl;
	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	//std::cout << cameraUp.x << " " << cameraUp.y << " " << cameraUp.z << std::endl;
}

Camera::~Camera()
{

}

glm::vec3 Camera::getPos() const	//Get camera position vector
{
	return _cameraPos;
}

void Camera::setPos(const glm::vec3 &newPos)
{
	_cameraPos = newPos;
	//std::cout << _cameraPos.x << " " << _cameraPos.y << " " << _cameraPos.z << std::endl;
}

glm::vec3 Camera::getFront() const //Get camera front vector
{
	return _cameraFront;
}

glm::vec3 Camera::getUp() const //Get camera up vector
{
	return _cameraUp;
}

void Camera::setFov(double fov)
{
	_fov = fov;
}

double Camera::getFov() const
{
	return _fov;
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = _movementSpeed *deltaTime;

	if (direction == Camera_Movement::BACKWARD)
		_cameraPos -= _cameraFront * velocity;
	else if (direction == Camera_Movement::FORWARD)
		_cameraPos += velocity * _cameraFront;
	else if (direction == Camera_Movement::RIGHT)
		_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * velocity;
	else if (direction == Camera_Movement::LEFT)
		_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * velocity;
	
}
