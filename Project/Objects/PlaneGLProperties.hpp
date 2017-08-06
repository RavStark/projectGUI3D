#pragma once

#include "IObjectGLProperties.hpp"

class PlaneGLProperties : public IObjectGLProperties
{
public:
	PlaneGLProperties();
	~PlaneGLProperties();

	void initObjectGLProperties() const;
	GLuint getVAO() const { return planeVAO; }
	GLuint getVBO() const { return planeVBO; }
private:
	mutable GLuint planeVAO, planeVBO;
};