#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
{
	std::ifstream iVertexShaderFile;
	std::ifstream iFragmentShaderFile;

	std::string vertexShaderStr;
	std::string fragmentShaderStr;

	iVertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	iFragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		iVertexShaderFile.open(vertexShaderPath);
		iFragmentShaderFile.open(fragmentShaderPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << iVertexShaderFile.rdbuf();
		fShaderStream << iFragmentShaderFile.rdbuf();

		vertexShaderStr = vShaderStream.str();
		fragmentShaderStr = fShaderStream.str();

		iVertexShaderFile.close();
		iFragmentShaderFile.close();
	}
	catch (const std::ifstream::failure &e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " << e.what() << std::endl;
	}

	GLuint vertexShader = this->createShader(vertexShaderStr.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShader = this->createShader(fragmentShaderStr.c_str(), GL_FRAGMENT_SHADER);

	_program = glCreateProgram();
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);
	glLinkProgram(_program);
	// Print linking errors if any

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{

}

GLuint Shader::createShader(const GLchar * source, GLenum type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

void Shader::use()
{
	glUseProgram(_program);
}

GLuint Shader::getProgram() const
{
	return _program;
}

void Shader::setInt(const char* dataName, const GLint &data)
{
	glUniform1i(glGetUniformLocation(_program, dataName), data);
}

void Shader::setFloat(const char* dataName, const GLfloat &data)
{
	glUniform1f(glGetUniformLocation(_program, dataName), data);
}

void Shader::setVec3(const char* name, const glm::vec3 &value)
{
	glUniform3fv(glGetUniformLocation(_program, name), 1, &value[0]);
}

void Shader::setVec3(const char* name, const GLfloat& value)
{
	glUniform3f(glGetUniformLocation(_program, name), value, value, value);
}


void Shader::setVec3(const char* name, const GLfloat& x, const GLfloat& y, const GLfloat& z)
{
	glUniform3f(glGetUniformLocation(_program, name), x, y, z);
}

void Shader::setMat4(const char* name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(_program, name), 1, GL_FALSE, glm::value_ptr(mat));
}