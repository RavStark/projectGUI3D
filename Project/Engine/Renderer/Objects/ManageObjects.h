#pragma once

#include <memory>
#include <unordered_map>

typedef unsigned int GLuint;
template<class T, class V>
class ManageObjects
{
public:
	ManageObjects()
	{
		_objectGLProperties = std::make_unique<V>();
		_objectGLProperties->initObjectGLProperties();
	}
	~ManageObjects() {}
	GLuint getVAO() const
	{
		return _objectGLProperties->getVAO();
	}
private:
	std::unique_ptr<V> _objectGLProperties;
	std::unordered_map<unsigned, std::shared_ptr<T>>  _mapObjects;
};

