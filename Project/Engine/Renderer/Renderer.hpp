#pragma once
#include "GL\glew.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Renderer/Shader.hpp"
#include <vector>
class LightsManager;
class ObjectsManager;
class Object;
class PointLight;
class DirectionLight;
class Camera;
class TextureManager;
class ModelRenderer;

class Renderer
{
public:
	enum Type {
		LIGHT,
		DEFAULT
	};
	explicit Renderer(const std::shared_ptr<Camera>& camera, const std::shared_ptr<TextureManager> &textureManager);
	
	void addModel(const char *path, const glm::vec3 &pos, const glm::vec3 &size = glm::vec3(1.0f));
	void addObject(const glm::vec3 &pos, const glm::vec3 &size, const glm::vec3 &color = glm::vec3(1.f));
	void addLight(const std::shared_ptr<PointLight>& obj);
	void addLight(const std::shared_ptr<DirectionLight>& obj);
	void update();
	void draw();
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
private:
	
	std::shared_ptr<Camera> _camera = nullptr;
	std::shared_ptr<TextureManager> _textureManager = nullptr;

	std::shared_ptr<LightsManager> _lightsManager = nullptr;
	std::shared_ptr<ObjectsManager> _objectsManager = nullptr;

	
	
	std::shared_ptr<Shader> _simpleShader = nullptr;
	std::shared_ptr<Shader> _simpleModelShader = nullptr;
	//std::shared_ptr<Shader> _lightShader = nullptr;
	std::shared_ptr<Shader> _multipleLightingShader = nullptr;

	//tmp list model
	std::vector<std::shared_ptr<ModelRenderer>> _models;
};