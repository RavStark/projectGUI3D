#include "PlaneGLProperties.hpp"
#include "GL\glew.h"

PlaneGLProperties::PlaneGLProperties()
	: IObjectGLProperties()
{

}

PlaneGLProperties::~PlaneGLProperties()
{

}

void PlaneGLProperties::initObjectGLProperties() const
{
	GLfloat verticesPlane[] = {
		// Positions          // Colors           // Texture Coords   //Normal
		//face down
		-0.5f,-0.5f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};
	
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPlane), verticesPlane, GL_STATIC_DRAW);

	glBindVertexArray(planeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Nomal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}