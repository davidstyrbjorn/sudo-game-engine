#include "sprite_component.h"
#include"../../gl_include.h"

#include"../../sudo.h"

#include"../SOIL2/SOIL2.h"

namespace sudo { namespace ecs { 

	SpriteComponent::SpriteComponent(char* a_imagePath, math::Vector2 &a_size) 
	{
		m_componentName = "SpriteComponent";

		m_imagePath = a_imagePath;

		m_size = a_size;
	}

	void SpriteComponent::Start()
	{
		float vertices[] = {
			// Vertex data					  color data		         									
			0, 0, 0.0f,						    1, 1, 1,
			0, m_size.getY(), 0.0f,				1, 1, 1,
			m_size.getX(), m_size.getY(), 0.0f,	1, 1, 1,
			m_size.getX(), 0.0f, 0.0f,			1, 1, 1
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
		m_vertexBuffer = new graphics::VertexBuffer(vertices, sizeof(vertices));

		/* Index buffer */
		m_elementBuffer = new graphics::Buffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

		/* Texture loading and binding etc */
		glEnable(GL_BLEND);
		glBlendFunc(GL_BLEND, GL_ONE_MINUS_SRC_ALPHA);

		int width, height;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* image = SOIL_load_image(m_imagePath, &width, &height, 0, SOIL_LOAD_RGBA);
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

} }