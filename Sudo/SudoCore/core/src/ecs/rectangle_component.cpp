#include"rectangle_component.h"

#include"../../sudo.h"
#include"../../gl_include.h"

namespace sudo { namespace ecs {

	RectangleComponent::RectangleComponent(math::Vector2 &a_size, math::Vector4 &a_color)
	{
		m_componentName = "RectangleComponent";

		m_size = a_size;
		m_color = a_color;
	}

	RectangleComponent::~RectangleComponent() 
	{
		delete m_vertexArray;
		delete m_vertexBuffer;
		delete m_elementBuffer;
	}

	void RectangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;
		
		float vertices[] = {
			// Vertex data								         Color data									
			0, 0, 0.0f,							m_color.getX(), m_color.getY(), m_color.getZ(),
			0, m_size.getY(), 0.0f,				m_color.getX(), m_color.getY(), m_color.getZ(),
			m_size.getX(), m_size.getY(), 0.0f,	m_color.getX(), m_color.getY(), m_color.getZ(),
			m_size.getX(), 0.0f, 0.0f,			m_color.getX(), m_color.getY(), m_color.getZ()
		};	
		unsigned int indices[] = {
			0,1,2,
			0,2,3
		};
		float textureCoords[] = {
			0,0,
			0,1,
			1,1,
			1,0,
		};

		glewInit();
		glewExperimental = true;

		/* Vertex array object */
		m_vertexArray = new graphics::VertexArrayBuffer();
		m_vertexArray->bind();

		/* Vertex buffer object */
		m_vertexBuffer = new graphics::VertexBuffer(vertices, sizeof(vertices));

		/* Index buffer */
		m_elementBuffer = new graphics::Buffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));
	}
	   
	void RectangleComponent::bind() 
	{
		m_vertexArray->bind();
	}

	void RectangleComponent::unbind() 
	{
	}

	void RectangleComponent::recolored()
	{
		/*
		float colors[] = {
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
		};

		glBindBuffer(GL_ARRAY_BUFFER, CBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
		*/
	}

	void RectangleComponent::resized()
	{
		/* Make sure the shape stays at it's position when resizing the vertices */
		math::Vector2 deltaChange = m_size - m_sizeBeforeReisze;
		m_entityTransform->position = math::Vector3(m_entityTransform->position.getX() - (deltaChange.getX() / 2),
			m_entityTransform->position.getY() - (deltaChange.getY() / 2),
			m_entityTransform->position.getZ());
		/*
		float vertices[] = {
			0, 0, 0.0f,
			0, m_size.getY(), 0.0f,
			m_size.getX(), m_size.getY(), 0.0f,
			m_size.getX(), 0.0f, 0.0f
		};
		uint indices[] = {
			0,1,2,
			0,2,3
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		*/
	}

} } 