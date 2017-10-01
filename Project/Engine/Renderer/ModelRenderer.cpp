#include "ModelRenderer.hpp"
#include <iostream>

#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Engine/Camera/CameraFps.hpp"
#include "Shader.hpp"
#include "Model.hpp"

ModelRenderer::ModelRenderer(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Model> &model, const glm::vec3 &pos, const glm::vec3 &size)
	: _model(model),
	Object(shader, pos, size, glm::vec3(1.0))
{
	
}

ModelRenderer::~ModelRenderer()
{

}

void ModelRenderer::initRenderData()
{
	
}

void ModelRenderer::draw(const glm::mat4 &view, const glm::mat4 &projection) const
{

}

void ModelRenderer::draw(const std::shared_ptr<TextureManager>& textureManger, const std::shared_ptr<Camera> &camera) const
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

	_model->Draw(*this->_shader.get());
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textureManger->getTexture("container"));
//	glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, textureManger->getTexture("container2_specular"));

}