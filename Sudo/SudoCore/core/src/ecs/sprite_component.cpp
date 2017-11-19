#include "sprite_component.h"
#include"../../gl_include.h"

#include"../../sudo.h"

#include"../SOIL2/SOIL2.h"

namespace sudo { namespace ecs {

	SpriteComponent::SpriteComponent(char* a_imagePath)
	{
		// Used when loading the image
		m_imagePath = a_imagePath;

		// m_size is set when loading the texture 
		m_color = math::Vector4(1, 1, 1, 1);

		// Used when shading
		m_type = sudo::RenderableType::SPRITE;
	}

	void SpriteComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;

		/*
		int width, height;
		unsigned char* image = SOIL_load_image(m_imagePath, &width, &height, 0, SOIL_LOAD_RGBA);
		m_size = math::Vector2(width, height);
		if (image == nullptr) 
		{	
			DEBUG::getInstance()->printMessage( (std::string("Failed to load image at path: \"") + std::string(m_imagePath)).c_str(), sudo::LogType::Error);
		}

		// Texture loading and binding etc 
		glEnable(GL_BLEND);
		glBlendFunc(GL_BLEND, GL_ONE_MINUS_SRC_ALPHA);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		*/
	}

	SpriteComponent::~SpriteComponent()
	{

	}

} }