#include"../include/graphics/texture.h"
#include"../include/debug.h"
#include"../include/gl_include.h"

#include<string>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/graphics/stb/stb_image.h"

namespace sudo { namespace graphics {

	Texture::Texture()
	{

	}

	Texture::Texture(char* a_imagePath)
	{
		this->loadImage(a_imagePath);
	}

	void Texture::loadImage(char * a_imagePath)
	{
		m_imagePath = a_imagePath;

		unsigned char* m_imageData = stbi_load(a_imagePath, &m_width, &m_height, 0, STBI_rgb);

		if (m_imageData == nullptr)
		{
			DEBUG::getInstance()->printMessage((std::string("Failed to load image at path: \"") + std::string(a_imagePath)).c_str(), sudo::LogType::Error);
		}

		// Generate and bind buffer
		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_2D, m_texId);

		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageData);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// End
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(m_imageData);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_texId);
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_texId);
	}
} }