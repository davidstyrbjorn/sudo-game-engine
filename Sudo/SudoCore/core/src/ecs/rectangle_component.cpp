#include"rectangle_component.h"

#include"../../sudo.h"
#include"../../gl_include.h"

#include"../SOIL2/SOIL2.h"

namespace sudo { namespace ecs {

	RectangleComponent::RectangleComponent(math::Vector2 &a_size, math::Vector4 &a_color)
	{
		m_componentName = "RectangleComponent";

		m_size = a_size;
		m_color = a_color;
	}

	RectangleComponent::~RectangleComponent() 
	{

	}

	void RectangleComponent::Start()
	{
		m_entityTransform = m_entityHolder->transform;

		float vertices[] = {
			0, 0, 0.0f,
			0, m_size.getY(), 0.0f,
			m_size.getX(), m_size.getY(), 0.0f,
			m_size.getX(), 0.0f, 0.0f
		};	
		unsigned int indices[] = {
			0,1,2,
			0,2,3
		};
		float colors[] = {
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
		};
		float textureCoords[] = {
			0,0,
			0,1,
			1,1,
			1,0,
		};

		glewInit();
		glewExperimental = true;

		// Vertex Array Object
		vertexArray = new graphics::VertexArrayBuffer();
		vertexArray->bind();

		// VBO (vertices)
		vertexBufferObject = new graphics::BufferObject();
		vertexBufferObject->init<float>(GL_ARRAY_BUFFER, vertices, 0, 3);

		// CBO (colors)
		colorBufferObject = new graphics::BufferObject();
		colorBufferObject->init<float>(GL_ARRAY_BUFFER, colors, 1, 3);

		// EBO (indices)
		elementBufferObject = new graphics::BufferObject();
		elementBufferObject->init<unsigned int>(GL_ELEMENT_ARRAY_BUFFER, indices, -1, 2);

		// Vertex Buffer Object
		/*
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		// Color Buffer Object
		glGenBuffers(1, &CBO);
		glBindBuffer(GL_ARRAY_BUFFER, CBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_READ);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(1);  

		// Index buffer
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Texture coords buffer object
		glGenBuffers(1, &TCBO);
		glBindBuffer(GL_ARRAY_BUFFER, TCBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_READ);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
		glEnableVertexAttribArray(2);
		*/

		//glBindVertexArray(0);

		// Texture test
		/*
		glEnable(GL_BLEND);
		glBlendFunc(GL_BLEND, GL_ONE_MINUS_SRC_ALPHA);

		int width, height;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char *image = SOIL_load_image("D://sample.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		*/
	}
	   
	void RectangleComponent::bind() 
	{
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture);

		vertexArray->bind();
		//vertexBufferObject->bind();
		//elementBufferObject->bind();
	}

	void RectangleComponent::unbind() 
	{
		vertexArray->unbind();
	}

	void RectangleComponent::recolored()
	{
		float colors[] = {
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
			m_color.getX(), m_color.getY(), m_color.getZ(),
		};

		glBindBuffer(GL_ARRAY_BUFFER, CBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
	}

	void RectangleComponent::resized()
	{
		/* Make sure the shape stays at it's position when resizing the vertices */
		math::Vector2 deltaChange = m_size - m_sizeBeforeReisze;
		m_entityTransform->position = math::Vector3(m_entityTransform->position.getX() - (deltaChange.getX() / 2),
			m_entityTransform->position.getY() - (deltaChange.getY() / 2),
			m_entityTransform->position.getZ());

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
	}

} } 