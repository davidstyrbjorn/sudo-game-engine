#include "sprite_component.h"
#include"../../gl_include.h"

#include"../graphics/texture.h"
#include"entity.h"

namespace sudo { namespace ecs {

	SpriteComponent::SpriteComponent(char* a_imagePath)
	{
		// Used when loading the image
		m_imagePath = a_imagePath;

		// m_size is set when loading the texture 
		m_color = math::Color(255, 255, 255, 255);

		// Initialize sprite texture
		m_texture = new graphics::Texture(a_imagePath);

		m_size = math::Vector2(m_texture->getWidth(), m_texture->getHeight());
	}

	void SpriteComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;
	}

	SpriteComponent::~SpriteComponent()
	{

	}

} }