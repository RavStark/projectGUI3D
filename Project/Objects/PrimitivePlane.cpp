#include "PrimitivePlane.hpp"
#include <iostream>

#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

PrimitivePlane::PrimitivePlane()
{
	
}

PrimitivePlane::~PrimitivePlane()
{

}

void PrimitivePlane::setTranslate(glm::vec3 translate)
{
	_model = glm::translate(_model, translate);
}

glm::mat4 PrimitivePlane::getModel() const {
	return _model;
}