#pragma once

#include <glm/glm.hpp>

typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;

class ILight
{
public:
	explicit ILight(const glm::vec3 &color = glm::vec3(1.f), const glm::vec3 &ambient = glm::vec3(0.05f), const glm::vec3 &diffuse = glm::vec3(0.8f), const glm::vec3 &specular = glm::vec3(1.0f))
		:
		_color(color),
		_ambient(ambient),
		_diffuse(diffuse),
		_specular(specular),
		_constant(1.0f),
		_linear(0.09f),
		_quadratic(0.032f)
	{

	}
	virtual ~ILight(){}

	void setColor(const glm::vec3 &color)
	{
		_color = color;
	}
	glm::vec3 getColor(void) const
	{
		return _color;
	}
	void setAmbient(const glm::vec3 &ambient)
	{
		_ambient = ambient;
	}
	glm::vec3 getAmbient(void) const
	{
		return _ambient;
	}
	void setDiffuse(const glm::vec3 &diffuse)
	{
		_diffuse = diffuse;
	}
	glm::vec3 getDiffuse(void) const
	{
		return _diffuse;
	}
	void setSpecular(const glm::vec3 &specular)
	{
		_specular = specular;
	}
	glm::vec3 getSpecular(void) const
	{
		return _specular;
	}
	void setConstant(const GLfloat &constant)
	{
		_constant = constant;
	}
	GLfloat getConstant(void) const
	{
		return _constant;
	}
	void setLinear(const GLfloat &linear)
	{
		_linear = linear;
	}
	GLfloat getLinear(void) const
	{
		return _linear;
	}
	void setQuadratic(const GLfloat &quadratic)
	{
		_quadratic = quadratic;
	}
	GLfloat getQuadratic(void) const
	{
		return _quadratic;
	}
	
protected:
	glm::vec3 _color;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	GLfloat _constant;
	GLfloat _linear;
	GLfloat _quadratic;
};