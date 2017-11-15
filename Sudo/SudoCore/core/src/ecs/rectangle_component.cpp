#include"rectangle_component.h"

#include"../../sudo.h"
#include"../../gl_include.h"
#include"../../definitions.h"

namespace sudo { namespace ecs {

	RectangleComponent::RectangleComponent(math::Vector2 &a_size, math::Vector4 &a_color)
	{
		// Arbitary shape values
		m_size = a_size;
		m_color = a_color;

		// Used when shading 
		m_type = sudo::RenderableType::SHAPE;
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

		math::Vector4 colorVector = math::Vector4(m_color.x, m_color.y, m_color.z, m_color.w);
		graphics::VertexData vertices_[] = {
			graphics::VertexData(math::Vector3(0.0f,0.0f,0.0f),			colorVector, math::Vector2(0,0)),
			graphics::VertexData(math::Vector3(0.0f,m_size.y,0.0f),		colorVector, math::Vector2(0,0)),
			graphics::VertexData(math::Vector3(m_size.x,m_size.y,0.0f), colorVector, math::Vector2(0,0)),
			graphics::VertexData(math::Vector3(m_size.x,0.0f,0.0f),		colorVector, math::Vector2(0,0))
		};
		unsigned int indices[] = {
			0,1,2,
			0,2,3
		};

		glewInit();
		glewExperimental = true;

		/* Vertex array object */
		m_vertexArray = new graphics::VertexArrayBuffer();
		m_vertexArray->bind();

		/* Vertex buffer object */
		m_vertexBuffer = new graphics::VertexBuffer(vertices_, sizeof(vertices_));

		/* Index buffer */
		m_elementBuffer = new graphics::Buffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));
	}
	   
	void RectangleComponent::bind() 
	{
		m_vertexArray->bind();
	}

	void RectangleComponent::unbind()
	{
		m_vertexArray->unbind();
	}

	void RectangleComponent::recolored()
	{
		m_vertexArray->bind();
		m_vertexBuffer->dataModified(m_color);
	}

	void RectangleComponent::resized()
	{
		/* Make sure the shape stays at it's position when resizing the vertices */
		math::Vector2 deltaChange = m_size - m_sizeBeforeReisze;
		m_entityTransform->position = math::Vector3(m_entityTransform->position.x - (deltaChange.x / 2),
			m_entityTransform->position.y - (deltaChange.y / 2),
			m_entityTransform->position.z);

		float vertices[] = {
			// Vertex data								         Color data									
			0, 0, 0.0f,							m_color.x, m_color.y, m_color.z,
			0, m_size.y, 0.0f,				m_color.x, m_color.y, m_color.z,
			m_size.x, m_size.y, 0.0f,	m_color.x, m_color.y, m_color.z,
			m_size.x, 0.0f, 0.0f,			m_color.x, m_color.y, m_color.z,

		};

		m_vertexArray->bind();
		m_vertexBuffer->dataModified(vertices, sizeof(vertices));
	}

} } 