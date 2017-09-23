#include "TextureManager.hpp"
#include <iostream>
#include <SOIL.h>
#include "GL\glew.h"


	TextureManager::TextureManager()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	TextureManager::~TextureManager()
	{

	}

	void TextureManager::loadNewTexture2D(const std::string &name, const char * path, GLint texture_wrap_s, GLint texture_wrap_t, GLint texture_min_filter, GLint texture_mag_filter)
	{
		int width, height = 0;
		unsigned char * image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
		if (image == 0)
		{
			std::cerr << "TEXTUREMANAGER::LOADNEWTEXTURE::FAILED " << path << std::endl;
			return;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
											   // Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_min_filter);
		// Load image, create texture and generate mipmaps
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);

		_textureData.emplace(std::pair < const std::string, GLuint>(name, texture));

		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	}

	GLuint TextureManager::getTexture(const std::string &name) const
	{
		auto it = _textureData.find(name);
		if (it != _textureData.end())
			return it->second;
		else
			std::cerr << "TEXTUREMANAGER::GETTEXTURE::FAILED " << name.c_str() << std::endl;
		return 0; // BAD BUT RETURN DEFAULT TEXTURE ID
	}
