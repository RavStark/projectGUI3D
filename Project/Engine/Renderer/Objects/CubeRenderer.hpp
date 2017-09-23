#pragma once

#include <glm/glm.hpp>
#include "Object.hpp"

typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;

class CubeRenderer : public Object
{
public:
	explicit CubeRenderer(const std::shared_ptr<Shader>& shader, const glm::vec3 &pos, const glm::vec3 &size = glm::vec3(1.f), const glm::vec3& color = glm::vec3(1.f));
	~CubeRenderer();

	virtual void initRenderData();
	virtual void draw(const glm::mat4 &view, const glm::mat4 &projection) const ;
	virtual void draw(const std::shared_ptr<TextureManager>& textureManger, const std::shared_ptr<Camera> &camera) const ;

};