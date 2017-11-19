#include"triangle_component.h"

#include"../../sudo.h"
#include"../../gl_include.h"

namespace sudo { namespace ecs {

	TriangleComponent::TriangleComponent(math::Vector2 & a_size, math::Vector4 &a_color)
	{
		// Arbitary shape values
		m_size = a_size;
		m_color = a_color;

		// Used when shading 
		m_type = sudo::RenderableType::SHAPE;
	}

	TriangleComponent::~TriangleComponent() 
	{
	
	}

	void TriangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;
	}

	const graphics::VertexData * TriangleComponent::GetPrimitiveData() const
	{
		graphics::VertexData vertices[] = {
			graphics::VertexData(math::Vector3(m_entityTransform->position.x, m_entityTransform->position.y, 0), m_color, math::Vector2(0,0)),
			graphics::VertexData(math::Vector3(m_entityTransform->position.x, m_entityTransform->position.y + m_size.y, 0), m_color, math::Vector2(0,0)),
			graphics::VertexData(math::Vector3(m_entityTransform->position.x + m_size.x, m_entityTransform->position.y + m_size.y, 0), m_color, math::Vector2(0,0))
		};

		return vertices;
	}

} }