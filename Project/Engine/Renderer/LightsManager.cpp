#include "LightsManager.hpp"
#include "Lights/PointLight.hpp"
#include "Lights/DirectionLight.hpp"
#include <iostream>

#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


LightsManager::LightsManager()
{

}

LightsManager::~LightsManager()
{}

void LightsManager::addLight(const std::shared_ptr<PointLight>&pointlight)
{
	_pointLights.push_back(pointlight);
}

void LightsManager::addLight(const std::shared_ptr<DirectionLight>&dirlight)
{
	_dirLights.push_back(dirlight);
}

std::vector<std::shared_ptr<PointLight>> LightsManager::getPointLights() const
{
	return _pointLights;
}

std::vector<std::shared_ptr<DirectionLight>> LightsManager::getDirectionLights() const
{
	return _dirLights;
}