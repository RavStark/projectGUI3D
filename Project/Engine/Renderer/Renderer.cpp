#include <string>
#include "Renderer.hpp"
#include "Engine/Renderer/LightsManager.hpp"
#include "Engine/Renderer/ObjectsManager.hpp"
#include "Engine/Renderer/Objects/CubeRenderer.hpp"
#include "Engine/Renderer/Lights/PointLight.hpp"
#include "Shader.hpp"
//#include "Engine/Renderer/Shader.hpp"
//shaders


Renderer::Renderer(const std::shared_ptr<Camera>& camera, const std::shared_ptr<TextureManager> &textureManager)
	: _camera(camera), _textureManager(textureManager)
{
	_lightsManager = std::make_shared<LightsManager>();
	_objectsManager = std::make_shared<ObjectsManager>(_camera, _textureManager);
	_planeShader = std::make_shared<Shader>("./Project/Shaders/MultipleLighting.vs", "./Project/Shaders/MultipleLightingWithoutText.frag");
	_simpleShader = std::make_shared<Shader>("./Project/Shaders/Color.vs", "./Project/Shaders/Color.frag");
	_multipleLightingShader = std::make_shared<Shader>("./Project/Shaders/MultipleLighting.vs", "./Project/Shaders/MultipleLighting.frag");
	
}

void Renderer::addObject(const glm::vec3 &pos, Renderer::Type t)
{
	std::shared_ptr<Shader> shader;
	//if (t == Type::LIGHT)
	//	shader = _lightShader;
	//else
		shader = _simpleShader;
	auto cubeRenderer = std::make_shared<CubeRenderer>(_simpleShader, pos);
	cubeRenderer->initRenderData();
	_objectsManager->addObject(cubeRenderer);
}

void Renderer::addLight(const std::shared_ptr<PointLight>& obj)
{
	_lightsManager->addLight(obj);
}

void Renderer::addLight(const std::shared_ptr<DirectionLight>& obj)
{
	_lightsManager->addLight(obj);
}

void Renderer::update()
{

}

void Renderer::draw()
{

	_multipleLightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	_multipleLightingShader->setVec3("dirLight.ambient", 1.0f);
	_multipleLightingShader->setVec3("dirLight.diffuse", 1.0f);
	_multipleLightingShader->setVec3("dirLight.specular", 1.0f);
	unsigned idx = 0;
	//Set light shader 4 PointLights Max for now
	for (auto light : _lightsManager->getPointLights())
	{
		if (idx == 4)
			break;
		_multipleLightingShader->setVec3(std::string("pointLights["+std::to_string(idx) + "].position").c_str(), light->getPos());
		_multipleLightingShader->setVec3(std::string("pointLights[" + std::to_string(idx) + "].ambient").c_str(), light->getAmbient());
		_multipleLightingShader->setVec3(std::string("pointLights[" + std::to_string(idx) + "].diffuse").c_str(), light->getDiffuse());
		_multipleLightingShader->setVec3(std::string("pointLights[" + std::to_string(idx) + "].specular").c_str(), light->getSpecular());
		_multipleLightingShader->setFloat(std::string("pointLights[" + std::to_string(idx) + "].constant").c_str(), light->getConstant());
		_multipleLightingShader->setFloat(std::string("pointLights[" + std::to_string(idx) + "].linear").c_str(), light->getLinear());
		_multipleLightingShader->setFloat(std::string("pointLights[" + std::to_string(idx) + "].quadratic").c_str(), light->getQuadratic());
		idx++;
	}

	_simpleShader->setVec3("lightColor", 0.0f, 1.0f, 0.0f);
	_objectsManager->draw();
}