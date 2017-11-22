#include"texture.h"
#include"../SOIL2/SOIL2.h"
#include"../debug.h"

namespace sudo { namespace graphics {

		Texture::Texture() 
		{

		}

		Texture::Texture(char* a_imagePath) 
		{
			unsigned char* m_imageData = SOIL_load_image(a_imagePath, &m_width, &m_height, 0, SOIL_LOAD_RGBA);		
			if (m_imageData == nullptr)
			{
				DEBUG::getInstance()->printMessage((std::string("Failed to load image at path: \"") + std::string(a_imagePath)).c_str(), sudo::LogType::Error);
			}

			// OpenGL blendig
			glEnable(GL_BLEND);
			glBlendFunc(GL_BLEND, GL_ONE_MINUS_SRC_ALPHA);

			// Generate and bind buffer
			glGenTextures(1, &m_texId);
			glBindTexture(GL_TEXTURE_2D, m_texId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Give the image to OpenGL
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, m_imageData);
			glGenerateMipmap(GL_TEXTURE_2D);

			glActiveTexture(GL_TEXTURE0);

			// End
			SOIL_free_image_data(m_imageData);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_texId);
		}
} }