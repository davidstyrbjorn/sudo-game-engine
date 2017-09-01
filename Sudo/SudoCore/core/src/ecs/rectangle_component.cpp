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

		float vertices[] = {
			0, 0, 0.0f,
			width,height,0.0f,
			0,height,0.0f,
			width,0.0f,0.0f
		};

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);
	}

	void RectangleComponent::SetPosition(math::Vector3 &a_newPosition)
	{
		m_entityTransform->position = a_newPosition;
	}

	void RectangleComponent::SetScale(math::Vector3 &a_newScale)
	{
		std::cout << a_newScale << " Yeet scaled up" << std::endl;
	}

	void RectangleComponent::Scale(float a_magnitude)
	{
		m_entityTransform->scale = math::Vector3(m_entityTransform->scale.getX()*a_magnitude, m_entityTransform->scale.getY()*a_magnitude, m_entityTransform->scale.getZ()*a_magnitude);
	}

	void RectangleComponent::Move(math::Vector3 &a_direction, float a_magnitude)
	{

	}

} } 