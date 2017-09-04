#include"rectangle_component.h"

#include"../../sudo.h"
#include"../../gl_include.h"

namespace sudo { namespace ecs { 

	/* Constructor */
	RectangleComponent::RectangleComponent(math::Vector2 & a_size)
	{
		// Setting component name, from component base class
		m_componentName = "RectangleComponent";

		// Setting size, from Renderable2D base class
		size = a_size;
	}

	void RectangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;

		float vertices[] = {
			0, 0, 0.0f,
			0, size.getY(), 0.0f,
			size.getX(), size.getY(), 0.0f,
			size.getX(), 0.0f, 0.0f
		};
		uint indices[] = {
			0,1,2,
			0,2,3
		};

		glewInit();
		glewExperimental = true;

		// Vertex Array Object
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Index buffer
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);
	}
	   
	void RectangleComponent::bind() 
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	void RectangleComponent::unbind() 
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
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
		m_entityTransform->scale = math::Vector3(
			m_entityTransform->scale.getX()*a_magnitude,
			m_entityTransform->scale.getY()*a_magnitude,
			m_entityTransform->scale.getZ()*a_magnitude
		);
	}

} } 