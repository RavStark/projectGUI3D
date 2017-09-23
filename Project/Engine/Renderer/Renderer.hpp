#pragma once
#include "GL\glew.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Renderer/Shader.hpp"
class LightsManager;
class ObjectsManager;
class Object;
class PointLight;
class DirectionLight;
class Camera;
class TextureManager;


class Renderer
{
public:
	enum Type {
		LIGHT,
		DEFAULT
	};
	explicit Renderer(const std::shared_ptr<Camera>& camera, const std::shared_ptr<TextureManager> &textureManager);
	
	void addObject(const glm::vec3 &pos, Renderer::Type t = Renderer::Type::DEFAULT);
	void addLight(const std::shared_ptr<PointLight>& obj);
	void addLight(const std::shared_ptr<DirectionLight>& obj);
	void update();
	void draw();

private:
	std::shared_ptr<Camera> _camera = nullptr;
	std::shared_ptr<TextureManager> _textureManager = nullptr;

	std::shared_ptr<LightsManager> _lightsManager = nullptr;
	std::shared_ptr<ObjectsManager> _objectsManager = nullptr;

	/* TMP TEST SHADER */

	//Shader lightShader = Shader("./Project/Shaders/Light.vs", "./Project/Shaders/Color.frag");
	
	std::shared_ptr<Shader> _simpleShader = nullptr;
	std::shared_ptr<Shader> _planeShader = nullptr;
	//std::shared_ptr<Shader> _lightShader = nullptr;
	std::shared_ptr<Shader> _multipleLightingShader = nullptr;
};