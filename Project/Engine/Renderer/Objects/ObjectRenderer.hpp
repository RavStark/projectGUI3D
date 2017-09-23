#pragma once
#include <glm/glm.hpp>
typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;

class ObjectRenderer
{
public:
	explicit ObjectRenderer(const glm::vec3 &pos, const glm::vec3 &size = glm::vec3(1.f), const glm::vec3& color = glm::vec3(1.f));
	~ObjectRenderer();

private:
	glm::vec3 pos;
	glm::vec3 size;
	glm::vec3 rotate;

};