#include"../include/ecs/rectangle_component.h"

#include"../include/definitions.h"
#include"../include/math/math.h"

#include"../include/ecs/transform_component.h"
#include"../include/ecs/entity.h"

#include"../include/math/vector3.h"

namespace sudo { namespace ecs {

#define DEFAULT_SIZE 50
#define DEFAULT_COLOR math::Color::Red()

	RectangleComponent::RectangleComponent(math::Vector2 &a_size, math::Color &a_color)
	{
		// Arbitary shape values
		m_size = a_size;
		m_color = a_color;
		c_pointCount = 4;
	}

	RectangleComponent::RectangleComponent()
	{
		m_size = math::Vector2(DEFAULT_SIZE, DEFAULT_SIZE);
		m_color = DEFAULT_COLOR;
		c_pointCount = 4;
	}

	RectangleComponent::~RectangleComponent() 
	{

	}

	void RectangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;
	}

	std::array<math::Vector3, 4> RectangleComponent::GetPrimitivePoints()
	{
		std::array<math::Vector3, 4> points;

		// Base values
		const Transform* transform = m_entityHolder->transform;
		const math::Vector2 size = this->m_size;
		const math::Vector3 position = m_entityHolder->transform->position;
		const float angle = m_entityHolder->transform->angle * DEG2RAD;

		if (angle == 0) {
			points[0] = transform->position;
			points[1] = math::Vector3(position.x, position.y + size.y, position.z);
			points[2] = math::Vector3(position.x + size.x, position.y + size.y, position.z);
			points[3] = math::Vector3(position.x + size.x, position.y, position.z);
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
		points[0] = math::Vector3(rotatedX + cx, rotatedY + cy, position.z);

		// Position 2											
		tempX = position.x - cx;
		tempY = (position.y + size.y) - cy;
		rotatedX = tempX * cos(angle) - tempY * sin(angle);
		rotatedY = tempX * sin(angle) + tempY * cos(angle);
		points[1] = math::Vector3(rotatedX + cx, rotatedY + cy, position.z);

		// Position 3											
		tempX = (position.x + size.x) - cx;
		tempY = (position.y + size.y) - cy;
		rotatedX = tempX * cos(angle) - tempY * sin(angle);
		rotatedY = tempX * sin(angle) + tempY * cos(angle);
		points[2] = math::Vector3(rotatedX + cx, rotatedY + cy, position.z);

		// Position 4											
		tempX = (position.x + size.x) - cx;
		tempY = position.y - cy;
		rotatedX = tempX * cos(angle) - tempY * sin(angle);
		rotatedY = tempX * sin(angle) + tempY * cos(angle);
		points[3] = math::Vector3(rotatedX + cx, rotatedY + cy, position.z);

		// Return the positions
		return points;
	}
} } 