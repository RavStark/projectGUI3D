#include "PlaneRenderer.hpp"
#include <iostream>

#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.hpp"

PlaneRenderer::PlaneRenderer(const std::shared_ptr<Shader>& shader, const glm::vec3 &pos, const glm::vec3 &size, const glm::vec3& color)
	:Object(shader, pos, size, color)
{
	
}

PlaneRenderer::~PlaneRenderer()
{

}

void PlaneRenderer::initRenderData()
{
	GLuint VBO;
	GLfloat verticesPlane[] = {
		// Positions          // Colors           // Texture Coords   //Normal
		//face down
		-0.5f,-0.5f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, -1.0f, 0.0f
	};
	
	glGenVertexArrays(1, &this->_vao);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPlane), verticesPlane, GL_STATIC_DRAW);

	glBindVertexArray(this->_vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Nomal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void PlaneRenderer::draw(const glm::mat4 &view, const glm::mat4 &projection) const
{
	// Prepare transformations
	this->_shader->use();
	glm::mat4 model;
	model = glm::translate(model, _pos);

	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
	model = glm::rotate(model, glm::radians(_rotate), glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));

	model = glm::scale(model, _size);
	glm::mat4 inverseModelView;
	this->_shader->setMat4("model", model);
	inverseModelView = glm::inverse(view * model);
	this->_shader->setMat4("inverseModelView", inverseModelView);
	this->_shader->setMat4("view", view);
	this->_shader->setMat4("projection", projection);
	this->_shader->setVec3("objectColor", _color);

	this->_shader->setInt("material.diffuse", 0);
	this->_shader->setInt("material.specular", 1);
	this->_shader->setInt("material.emission", 1);
	//glActiveTexture(GL_TEXTURE0);
	//texture.Bind();

	glBindVertexArray(this->_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}