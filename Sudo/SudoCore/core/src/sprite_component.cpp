#include "../include/ecs/sprite_component.h"
#include"../include/ecs/transform_component.h"

#include"../include/gl_include.h"

#include"../include/graphics/texture.h"
#include"../include/ecs/entity.h"
#include"../include/math/vector3.h"

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

	const math::Vector3 * SpriteComponent::GetPrimitivePoints()
	{
		// Final return value
		math::Vector3 points[4];

		// Base values
		const Transform* transform = m_entityHolder->transform;
		const math::Vector2 size = this->m_size;
		const math::Vector3 position = m_entityHolder->transform->position;
		const float angle = m_entityHolder->transform->angle * DEG2RAD;

		if (angle == 0) {
			points[0] = transform->position;
			points[1] = math::Vector3(transform->position.x, transform->position.y + size.y, transform->position.z);
			points[2] = math::Vector3(transform->position.x + size.x, transform->position.y + size.y, transform->position.z);
			points[3] = math::Vector3(transform->position.x + size.x, transform->position.y, transform->position.z);
			return points;
		}

		// Center of the rectangle
		float cx = transform->position.x + (size.x / 2);
		float cy = transform->position.y + (size.y / 2);

		// Position 1
		float tempX = transform->position.x - cx;
		float tempY = transform->position.y - cy;
		float rotatedX = tempX * cos(angle) - tempY * sin(angle);
		float rotatedY = tempX * sin(angle) + tempY * cos(angle);
		points[0] = math::Vector3(rotatedX - cx, rotatedY - cy, transform->position.y);

		// Position 2
		tempX = position.x - cx;
		tempY = (position.y + size.y) - cx;
		rotatedX = tempX * cos(angle) - tempY * sin(angle);
		rotatedY = tempX * sin(angle) + tempY * cos(angle);
		points[1] = math::Vector3(rotatedX - cx, rotatedY - cy, transform->position.y);

		// Position 3
		tempX = (position.x + size.x) - cx;
		tempY = (position.y + size.y) - cy;
		rotatedX = tempX * cos(angle) - tempY * sin(angle);
		rotatedY = tempX * sin(angle) + tempY * cos(angle);
		points[2] = math::Vector3(rotatedX - cx, rotatedY - cy, transform->position.y);

		// Position 4
		tempX = (position.x + size.x) - cx;
		tempY = position.y - cy;
		rotatedX = tempX * cos(angle) - tempY * sin(angle);
		rotatedY = tempX * sin(angle) + tempY * cos(angle);
		points[3] = math::Vector3(rotatedX - cx, rotatedY - cy, transform->position.y);

		// Return the positions
		return points;
	}

	SpriteComponent::~SpriteComponent()
	{

	}

} }