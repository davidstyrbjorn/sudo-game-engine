#include"triangle_component.h"

#include"../../sudo.h"
#include"../../gl_include.h"

namespace sudo { namespace ecs {

	TriangleComponent::TriangleComponent(math::Vector2 & a_size, math::Vector4 &a_color)
	{
		// Setting component name, from component base class
		m_componentName = "TriangleComponent";

		// Setting data inherited from Renderable2D base class
		m_size = a_size;
		m_color = a_color;
	}

	TriangleComponent::~TriangleComponent() 
	{
		delete m_vertexArray;
		delete m_vertexBuffer;
		delete m_elementBuffer;
	}

	void TriangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;

		float vertices[] = {
			// Vertex data                           Color data
			0, 0, 0.0f,								 m_color.getX(), m_color.getY(), m_color.getZ(),
			0, m_size.getY(), 0.0f,					 m_color.getX(), m_color.getY(), m_color.getZ(),
			m_size.getX(), m_size.getY(), 0.0f,		 m_color.getX(), m_color.getY(), m_color.getZ()
		};
		uint indices[] = {
			0,1,2,
		};

		glewInit();
		glewExperimental = true;

		// Vertex Array Object
		m_vertexArray = new graphics::VertexArrayBuffer();
		m_vertexArray->bind();

		// Vertex buffer and all it's data
		m_vertexBuffer = new graphics::VertexBuffer(vertices, sizeof(vertices), graphics::SudoBuferType::VERTEX_COLOR);

		// Element buffer
		m_elementBuffer = new graphics::Buffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));
	}

	void TriangleComponent::resized()
	{
		/* Make sure the shape stays at it's position when resizing the vertices */
		math::Vector2 deltaChange = m_size - m_sizeBeforeReisze;
		m_entityTransform->position = math::Vector3(m_entityTransform->position.getX() - (deltaChange.getX()/2),
			m_entityTransform->position.getY() - (deltaChange.getY()/2),
			m_entityTransform->position.getZ());

		/*
		float vertices[] = {
			0, 0, 0.0f,
			0, m_size.getY(), 0.0f,
			m_size.getX(), m_size.getY(), 0.0f,
		};
		uint indices[] = {
			0,1,2,
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		*/
	}

	void TriangleComponent::recolored()
	{
		/*
		float colors[] = {
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ()
		};

		glBindBuffer(GL_ARRAY_BUFFER, CBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
		*/
	}

	void TriangleComponent::bind()
	{
		m_vertexArray->bind();
	}

	void TriangleComponent::unbind()
	{

	}
} }