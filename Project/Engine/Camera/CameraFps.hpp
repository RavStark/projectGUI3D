#pragma once

#include "Camera.hpp"


class CameraFps : public Camera
{
public:
	CameraFps(const glm::vec3 &pos);
	CameraFps(const glm::vec3 &pos, int screenWidth, int screenHeight);
	~CameraFps();

	virtual glm::mat4 viewMatrix() const;
	virtual glm::mat4 projectionMatrix() const;
	virtual void updateDirection(float pitch, float yaw, float roll);
};