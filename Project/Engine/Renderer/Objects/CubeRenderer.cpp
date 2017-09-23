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
		// Positions          // Colors           // Texture Coords   //Normal
		//front
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0.0f, -1.0f, // Top Left
		0.5f,-0.5f, -0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  // Bottom Right
		-0.5f,-0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  // Bottom Left

		-0.5f,  0.5f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  0.0f, 0.0f, -1.0f, // Top Left
		0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  0.0f, 0.0f, -1.0f, // Top Right
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,  0.0f, 0.0f, -1.0f, // Bottom Right

		 //back
		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f,-0.5f, 0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,-0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f,-0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		//left
		-0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f,-0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		//right
		0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f,-0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		//face down
		-0.5f,-0.5f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		//face up
		-0.5f, 0.5f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	};
	
	glGenVertexArrays(1, &this->_vao);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
	glm::mat4 inverseModelView;
	glm::mat4 view;
	glm::mat4 projection;
	/* DEBUG*/
	this->_shader->setVec3("ourColor", 1.0f, 0.5f, 0.31f);
	/* ****** */
	this->_shader->setMat4("model", model);
	view = glm::translate(view, camera->getPos());
	inverseModelView = glm::inverse(camera->viewMatrix() * model);
	this->_shader->setMat4("inverseModelView", inverseModelView);
	this->_shader->setVec3("viewPos", camera->getPos());
	this->_shader->setMat4("view", camera->viewMatrix());
	this->_shader->setMat4("projection", camera->projectionMatrix());
	this->_shader->setVec3("objectColor", _color);
	this->_shader->setInt("material.diffuse", 0);
	this->_shader->setInt("material.specular", 1);
	this->_shader->setInt("material.emission", 1);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	this->_shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	//lightingShader.setVec3("lightPos", lightPos);

	/*
	Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
	the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
	by defining light types as classes and set their values in there, or by using a more efficient uniform approach
	by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
	*/
	// directional light
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureManger->getTexture("container"));
//	glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, textureManger->getTexture("container2_specular"));

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}