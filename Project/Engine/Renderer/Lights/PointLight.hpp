#pragma once

#include "../Lights/ILight.hpp"

typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;

class PointLight : public ILight
{
public:
	explicit PointLight(const glm::vec3&pos, const glm::vec3 &color = glm::vec3(1.f), const glm::vec3 &ambient = glm::vec3(0.05f), const glm::vec3 &diffuse = glm::vec3(0.8f), const glm::vec3 &specular = glm::vec3(1.0f));
	~PointLight();

	void setPos(const glm::vec3&pos);
	glm::vec3 getPos(void) const;
private:
	glm::vec3 _pos;

};