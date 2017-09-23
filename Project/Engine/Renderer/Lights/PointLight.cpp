#include "PointLight.hpp"
#include <iostream>

#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../TextureManager.hpp"

PointLight::PointLight(const glm::vec3&pos, const glm::vec3 &color, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
	:ILight(color, ambient, diffuse, specular),
	_pos(pos)
{
	
}

PointLight::~PointLight()
{

}

void PointLight::setPos(const glm::vec3&pos)
{
	_pos = pos;
}

glm::vec3 PointLight::getPos(void) const
{
	return _pos;
}