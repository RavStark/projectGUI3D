#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

#include "Shader.hpp"
typedef int GLint;
typedef unsigned int GLuint;
#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL.h>
#include <iostream>

class Model
{
public:
	/*  Functions   */
	Model(const char *path);
	void Draw(Shader shader);
private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;
	/*  Functions   */
	std::vector<Texture> textures_loaded;
	bool loadModel(const std::string &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string typeName);


	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;
		std::cout << filename << std::endl;
		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char *data = SOIL_load_image(filename.c_str(), &width, &height, &nrComponents, SOIL_LOAD_AUTO);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			SOIL_free_image_data(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			SOIL_free_image_data(data);
		}

		return textureID;
	}
};

