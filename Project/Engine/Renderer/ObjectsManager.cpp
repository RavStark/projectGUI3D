#include "ObjectsManager.hpp"
#include "Objects/Object.hpp"
#include "Engine/Camera/Camera.hpp"
#include "Engine/Renderer/TextureManager.hpp"
#include <iostream>

#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ObjectsManager::ObjectsManager(const std::shared_ptr<Camera> &camera, const std::shared_ptr<TextureManager> &textureManager)
	: _camera(camera), _textureManager(textureManager)
{

}

ObjectsManager::~ObjectsManager()
{}

void ObjectsManager::addObject(const std::shared_ptr<Object>&obj)
{
	if (obj)
	{
		auto p = std::make_pair(++_id, obj);
		if (_objectList.insert(p).second == false)
			std::cerr << "Object _id " << _id << "already exists" << std::endl;
	}
}

void ObjectsManager::draw()
{
	/* DRAW OBJECT */
	for (auto obj : _objectList)
	{
		obj.second->draw(_textureManager, _camera);
	}
}
