#include "Object.hpp"
#include <iostream>

#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../TextureManager.hpp"

Object::Object(const std::shared_ptr<Shader>& shader, const glm::vec3 &pos, const glm::vec3 &size, const glm::vec3& color)
	: _shader(shader), _pos(pos), _size(size), _color(color), _rotate(0)

{
	
}

Object::~Object()
{

}

void Object::setPos(const glm::vec3 &pos)
{
	_pos = pos;
}

glm::vec3 Object::getPos() const
{
	return _pos;
}

void Object::setSize(const glm::vec3 &size)
{
	_size = size;
}

glm::vec3 Object::getSize() const
{
	return _size;
}

void Object::setColor(const glm::vec3 &color)
{
	_color = color;
}

glm::vec3 Object::getColor() const
{
	return _color;
}

void Object::setRotate(const float &rotate)
{
	_rotate = rotate;
}

float Object::getRotate() const
{
	return _rotate;
}