#pragma once

#include <memory>
#include <vector>
class PointLight;
class DirectionLight;

typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;

class LightsManager
{
public:
	LightsManager();
	~LightsManager();

	void addLight(const std::shared_ptr<PointLight>&);
	void addLight(const std::shared_ptr<DirectionLight>&);

	std::vector<std::shared_ptr<PointLight>> getPointLights() const;
	std::vector<std::shared_ptr<DirectionLight>> getDirectionLights() const;
private:
	std::vector<std::shared_ptr<PointLight>> _pointLights;
	std::vector<std::shared_ptr<DirectionLight>> _dirLights;
};