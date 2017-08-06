#pragma once
#include "GL\glew.h"

class IObjectGLProperties
{
public:
	IObjectGLProperties() {};
	virtual void initObjectGLProperties() const = 0;
	virtual GLuint getVAO() const = 0;
};