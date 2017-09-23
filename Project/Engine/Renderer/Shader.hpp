#pragma once

#include "GL\glew.h"
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
	~Shader();

	void use();
	GLuint getProgram() const;

	//Set shaders properties
	void setInt(const char*, const GLint&);
	void setFloat(const char*, const GLfloat&);
	void setVec3(const char*, const glm::vec3&);
	void setVec3(const char*, const GLfloat&);
	void setVec3(const char*, const GLfloat&, const GLfloat&, const GLfloat&);
	void setMat4(const char*, const glm::mat4&);
private:
	GLuint createShader(const GLchar * source, GLenum type);
	GLuint _program;
};