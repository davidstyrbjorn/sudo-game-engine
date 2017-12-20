#include"../include/ecs/rectangle_component.h"

#include"../include/gl_include.h"
#include"../include/definitions.h"

#include"../include/ecs/transform_component.h"
#include"../include/ecs/entity.h"

namespace sudo { namespace ecs {

	RectangleComponent::RectangleComponent(math::Vector2 &a_size, math::Color &a_color)
	{
		// Arbitary shape values
		m_size = a_size;
		m_color = a_color;
	}

	RectangleComponent::~RectangleComponent() 
	{

	}

	void RectangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;
	}

	std::vector<graphics::VertexData> RectangleComponent::GetPrimitiveData() 
	{
		std::vector<graphics::VertexData> vertices = {
			// Triangle 1
			
			graphics::VertexData(math::Vector3((m_entityTransform->position.x),			   (m_entityTransform->position.y),				0), m_color, math::Vector2(0,0)),
			graphics::VertexData(math::Vector3((m_entityTransform->position.x),			   (m_entityTransform->position.y + m_size.y),  0), m_color, math::Vector2(0,1)),
			graphics::VertexData(math::Vector3((m_entityTransform->position.x + m_size.x), (m_entityTransform->position.y + m_size.y),  0), m_color, math::Vector2(1,1)),

			// Triangle 2
			graphics::VertexData(math::Vector3((m_entityTransform->position.x + m_size.x), (m_entityTransform->position.y + m_size.y),  0), m_color, math::Vector2(1,1)),
			graphics::VertexData(math::Vector3((m_entityTransform->position.x + m_size.x), (m_entityTransform->position.y),				0), m_color, math::Vector2(1,0)),
			graphics::VertexData(math::Vector3((m_entityTransform->position.x),			   (m_entityTransform->position.y),				0), m_color, math::Vector2(0,0))
			

			/*
			graphics::VertexData(m_entityTransform->position, m_color, math::Vector2(0,0)),
			graphics::VertexData(math::Vector3(m_entityTransform->position.x, m_entityTransform->position.y + m_size.y, 0), m_color, math::Vector2(1,0)),
			graphics::VertexData(math::Vector3(m_entityTransform->position.x + m_size.x, m_entityTransform->position.y + m_size.y, 0), m_color, math::Vector2(1,1)),
			graphics::VertexData(math::Vector3(m_entityTransform->position.x + m_size.x, m_entityTransform->position.y, 0), m_color, math::Vector2(0,1))
			*/
		};

		return vertices;
	}

} } 