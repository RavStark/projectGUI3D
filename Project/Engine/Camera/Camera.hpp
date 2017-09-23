#pragma once

#include <unordered_map>

#include <glm/glm.hpp> //glm function


class Camera
{
public:
	// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods

	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
	Camera(const glm::vec3 &pos);
	Camera(const glm::vec3 &pos, int screenWidth, int screenHeight);
	~Camera();

	virtual glm::mat4 viewMatrix() const = 0;
	virtual glm::mat4 projectionMatrix() const = 0;
	virtual void updateDirection(float yaw, float pitch, float roll) = 0;
	void processKeyboard(Camera_Movement, float deltaTime);
	glm::vec3 getPos() const; //Get camera position vector
	void setPos(const glm::vec3 &newPos);
	glm::vec3 getFront() const; //Get camera front vector
	glm::vec3 getUp() const; //Get camera up vector
	void setFov(double fov);
	double getFov() const;
protected:
	int _screenWidth = 800;
	int _screenHeight = 600;
	glm::vec3 _cameraPos;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;
	float _pitch = 0.0f;
	float _yaw = -90.0f;// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	float _fov = 45.f;
	float _xOffset = 0.0f;
	float _yOffset = 0.0f;
	float _movementSpeed = 2.5f;
};
