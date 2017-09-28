#include "sprite_component.h"
#include"../../gl_include.h"

#include"../../sudo.h"

#include"../SOIL2/SOIL2.h"

namespace sudo { namespace ecs {

	SpriteComponent::SpriteComponent(char* a_imagePath)
	{
		// Name of the component
		m_componentName = "SpriteComponent";

		// Used when loading the image
		m_imagePath = a_imagePath;

		// m_size is set when loading the texture 
		m_color = math::Vector4(1, 1, 1, 1);

		// Used when shading
		m_type = sudo::RenderableType::SPRITE;

		
	}

	void SpriteComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;

		int width, height;
		unsigned char* image = SOIL_load_image(m_imagePath, &width, &height, 0, SOIL_LOAD_RGBA);
		m_size = math::Vector2(width, height);

		float vertices[] = {
			// Vertex data					  color data	 texture coordinates	         									
			0, 0, 0.0f,						    1, 1, 1,         0,0,
			0, m_size.getY(), 0.0f,				1, 1, 1,         0,1,
			m_size.getX(), m_size.getY(), 0.0f,	1, 1, 1,		 1,1,
			m_size.getX(), 0.0f, 0.0f,			1, 1, 1,         1,0
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
		m_vertexBuffer = new graphics::VertexBuffer(vertices, sizeof(vertices), SudoBufferType::VERTEX_COLOR_TEXTURE);

		/* Index buffer */
		m_elementBuffer = new graphics::Buffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

		/* Texture loading and binding etc */
		glEnable(GL_BLEND);
		glBlendFunc(GL_BLEND, GL_ONE_MINUS_SRC_ALPHA);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	SpriteComponent::~SpriteComponent()
	{
		delete m_vertexArray;
		delete m_vertexBuffer;
		delete m_elementBuffer;
	}

	void SpriteComponent::bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		m_vertexArray->bind();
	}

	void SpriteComponent::unbind()
	{

	}

	void SpriteComponent::resized()
	{
		/* Make sure the shape stays at it's position when resizing the vertices */
		math::Vector2 deltaChange = m_size - m_sizeBeforeReisze;
		m_entityTransform->position = math::Vector3(m_entityTransform->position.getX() - (deltaChange.getX() / 2),
			m_entityTransform->position.getY() - (deltaChange.getY() / 2),
			m_entityTransform->position.getZ());

		float vertices[] = {
			// Vertex data					  color data	 texture coordinates	         									
			0, 0, 0.0f,						    1, 1, 1,         0,0,
			0, m_size.getY(), 0.0f,				1, 1, 1,         0,1,
			m_size.getX(), m_size.getY(), 0.0f,	1, 1, 1,		 1,1,
			m_size.getX(), 0.0f, 0.0f,			1, 1, 1,         1,0
		};

		m_vertexArray->bind();
		m_vertexBuffer->dataModified(vertices, sizeof(vertices));
	}

	void SpriteComponent::recolored()
	{
		float vertices[] = {
			// Vertex data					  color data	 texture coordinates	         									
			0, 0, 0.0f,						    1, 1, 1,         0,0,
			0, m_size.getY(), 0.0f,				1, 1, 1,         0,1,
			m_size.getX(), m_size.getY(), 0.0f,	1, 1, 1,		 1,1,
			m_size.getX(), 0.0f, 0.0f,			1, 1, 1,         1,0
		};

		m_vertexArray->bind();
		m_vertexBuffer->dataModified(vertices, sizeof(vertices));
	}

} }