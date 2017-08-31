#include"rectangle_component.h"

#include"../../sudo.h"

namespace sudo { namespace ecs { 

	/* Constructor */
	RectangleComponent::RectangleComponent() 
	{
		m_componentName = "RectangleComponent";
	}

	void RectangleComponent::Update()
	{
		std::cout << m_entityTransform->position << std::endl;
	}

	void RectangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;
	}

	void RectangleComponent::SetPosition(math::Vector2 &a_newPosition)
	{

	}

	void RectangleComponent::SetScale(math::Vector2 &a_newScale)
	{
		std::cout << a_newScale << " Yeet scaled up" << std::endl;
	}

	void RectangleComponent::Scale(float a_magnitude)
	{

	}

	void RectangleComponent::Move(math::Vector2 &a_direction, float a_magnitude)
	{

	}

} } 