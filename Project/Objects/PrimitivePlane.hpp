#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;

class PrimitivePlane
{
public:
	PrimitivePlane();
	~PrimitivePlane();
	void setTranslate(glm::vec3 translate);
	glm::mat4 getModel() const;
private:
	glm::mat4 _model;

	
};