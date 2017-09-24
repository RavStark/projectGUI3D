#include "CubeRenderer.hpp"
#include <iostream>

#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../LightsManager.hpp"
#include "../Shader.hpp"
#include "../TextureManager.hpp"
#include "Engine/Camera/CameraFps.hpp"

CubeRenderer::CubeRenderer(const std::shared_ptr<Shader>& shader, const glm::vec3 &pos, const glm::vec3 &size, const glm::vec3& color)
	: Object(shader, pos, size, color)
{
	
}

CubeRenderer::~CubeRenderer()
{

}

void CubeRenderer::initRenderData()
{
	GLuint VBO;
	//vertices for triangles
	GLfloat vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f

	};
	
	glGenVertexArrays(1, &this->_vao);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->_vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	/*// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);*/
	/**/
	// Nomal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CubeRenderer::draw(const glm::mat4 &view, const glm::mat4 &projection) const
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
	this->_shader->setMat4("viewPos", view);
	this->_shader->setMat4("projection", projection);
	this->_shader->setVec3("objectColor", _color);
	//glActiveTexture(GL_TEXTURE0);
	//texture.Bind();

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void CubeRenderer::draw(const std::shared_ptr<TextureManager>& textureManger, const std::shared_ptr<Camera> &camera) const
{
	// Prepare transformations

	
	this->_shader->use();
	glBindVertexArray(this->_vao);
	glm::mat4 model;
	model = glm::translate(model, _pos);

	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
	//model = glm::rotate(model, glm::radians(_rotate), glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));

	model = glm::scale(model, _size);
	glm::mat4 inverseModel;
	glm::mat4 view;
	glm::mat4 projection;
	/* DEBUG*/
	/* ****** */
	this->_shader->setMat4("model", model);
	view = glm::translate(view, camera->getPos());
	inverseModel = glm::inverse(model);
	//this->_shader->setMat4("inverseModel", inverseModel);
	//this->_shader->setVec3("viewPos", camera->getPos());
	this->_shader->setMat4("view", camera->viewMatrix());
	this->_shader->setMat4("projection", camera->projectionMatrix());

	//Default
	this->_shader->setVec3("material.ambient", _color);
	this->_shader->setVec3("material.diffuse", _color);
	this->_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	this->_shader->setFloat("material.shininess", 32.0f);

	
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textureManger->getTexture("container"));
//	glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, textureManger->getTexture("container2_specular"));

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}