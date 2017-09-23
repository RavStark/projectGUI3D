#pragma once

#include "../Lights/ILight.hpp"

typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;

class DirectionLight : public ILight
{
public:
	explicit DirectionLight(const glm::vec3&dir, const glm::vec3 &color = glm::vec3(1.f), const glm::vec3 &ambient = glm::vec3(0.05f), const glm::vec3 &diffuse = glm::vec3(0.8f), const glm::vec3 &specular = glm::vec3(1.0f));
	~DirectionLight();

	void setDir(const glm::vec3&dir);
	glm::vec3 getDir(void) const;
private:
	glm::vec3 _dir;

};