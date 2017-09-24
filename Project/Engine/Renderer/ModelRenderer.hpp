#pragma once

#include <glm/glm.hpp>
#include "Objects/Object.hpp"

typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;

class Model;

class ModelRenderer : public Object
{
public:
	explicit ModelRenderer(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Model> &model,const glm::vec3 &pos, const glm::vec3 &size = glm::vec3(1.f));
	~ModelRenderer();

	virtual void initRenderData();
	virtual void draw(const glm::mat4 &view, const glm::mat4 &projection) const ;
	virtual void draw(const std::shared_ptr<TextureManager>& textureManger, const std::shared_ptr<Camera> &camera) const ;

private:
	std::shared_ptr<Model> _model;
};