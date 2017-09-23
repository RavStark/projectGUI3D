#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

class Object;
class TextureManager;
class Camera;
typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;

class ObjectsManager
{
public:
	ObjectsManager(const std::shared_ptr<Camera> &camera, const std::shared_ptr<TextureManager> &textureManager);
	~ObjectsManager();

	void addObject(const std::shared_ptr<Object>&);
	void initRenderData();
	void update();
	void draw();
private:
	std::shared_ptr<Camera> _camera;
	std::shared_ptr<TextureManager> _textureManager;
	std::unordered_map<long long int, std::shared_ptr<Object>> _objectList;
	long long int _id = 0;
};