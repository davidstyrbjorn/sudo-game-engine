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
		delete m_vertexArray;
		delete m_vertexBuffer;
		delete m_elementBuffer;
	}

	void TriangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;

		float vertices[] = {
			// Vertex data                           Color data
			0, 0, 0.0f,								 m_color.x, m_color.y, m_color.z,
			0, m_size.y, 0.0f,						 m_color.x, m_color.y, m_color.z,
			m_size.x, m_size.y, 0.0f,				 m_color.x, m_color.y, m_color.z
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
		m_vertexBuffer = new graphics::VertexBuffer(vertices, sizeof(vertices), SudoBufferType::VERTEX_COLOR);

		// Element buffer
		m_elementBuffer = new graphics::Buffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));
	}

	void TriangleComponent::resized()
	{
		/* Make sure the shape stays at it's position when resizing the vertices */
		math::Vector2 deltaChange = m_size - m_sizeBeforeReisze;
		m_entityTransform->position = math::Vector3(m_entityTransform->position.x - (deltaChange.x/2),
			m_entityTransform->position.y - (deltaChange.y/2),
			m_entityTransform->position.z);

		float vertices[] = {
			// Vertex data                           Color data
			0, 0, 0.0f,								 m_color.x, m_color.y, m_color.z,
			0, m_size.y, 0.0f,					 m_color.x, m_color.y, m_color.z,
			m_size.x, m_size.y, 0.0f,		 m_color.x, m_color.y, m_color.z
		};

		m_vertexArray->bind();
		m_vertexBuffer->dataModified(vertices, sizeof(vertices));
	}

	void TriangleComponent::recolored()
	{
		float vertices[] = {
			// Vertex data                           Color data
			0, 0, 0.0f,								 m_color.x, m_color.y, m_color.z,
			0, m_size.y, 0.0f,					 m_color.x, m_color.y, m_color.z,
			m_size.x, m_size.y, 0.0f,		 m_color.x, m_color.y, m_color.z
		};

		m_vertexArray->bind();
		m_vertexBuffer->dataModified(vertices, sizeof(vertices));
	}

	void TriangleComponent::bind()
	{
		m_vertexArray->bind();
	}

	void TriangleComponent::unbind()
	{

	}
} }