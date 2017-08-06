#pragma once

#include <unordered_map>

typedef int GLint;
typedef unsigned int GLuint;
namespace Texture
{
	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();

		//GL_CLAMP_TO_EDGE
		//GL_REPEAT
		//GL_NEAREST
		//GL_LINEAR
		void loadNewTexture2D(const std::string &name, const char * path,
			GLint texture_wrap_s, GLint texture_wrap_t,
			GLint texture_min_filter, GLint texture_mag_filter);
		GLuint getTexture(const std::string &textureName) const;
	private:
		std::unordered_map<std::string, GLuint> _textureData;
	};
}