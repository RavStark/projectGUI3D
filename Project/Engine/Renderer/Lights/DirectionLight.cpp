#include "DirectionLight.hpp"
#include <iostream>

#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


DirectionLight::DirectionLight(const glm::vec3&dir,const glm::vec3 &color, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
	:ILight(color, ambient, diffuse, specular),
	_dir(dir)
{
	
}

DirectionLight::~DirectionLight()
{

}


void DirectionLight::setDir(const glm::vec3&dir)
{
	_dir = dir;
}

glm::vec3 DirectionLight::getDir(void) const
{
	return _dir;
}