#include"../include/ecs/triangle_component.h"

#include"../include/gl_include.h"

#include"../include/ecs/transform_component.h"
#include"../include/ecs/entity.h"

namespace sudo { namespace ecs {

	TriangleComponent::TriangleComponent(math::Vector2 & a_size, math::Color &a_color)
	{
		// Arbitary shape values
		m_size = a_size;
		m_color = a_color;
	}

	TriangleComponent::~TriangleComponent() 
	{
		
	}

	void TriangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;
	}
} }