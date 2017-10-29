#include"batch_render_system.h"

#include"../../gl_include.h"
#include"../../sudo.h"

#include"../graphics/renderable2d_temp.h"

namespace sudo { namespace sudo_system { 

	BatchRenderSystem::BatchRenderSystem()
	{

	}

	BatchRenderSystem::~BatchRenderSystem()
	{

	}

	void BatchRenderSystem::init()
	{
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// Generate the empty buffer with enough allocated memory
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), (const GLvoid*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), (const GLvoid*)(3 * GL_FLOAT));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLushort indicies[RENDERER_INDICIES_SIZE];
			
	}

	void BatchRenderSystem::flush()
	{

	}

	void BatchRenderSystem::submit(const graphics::Renderable2D &a_other)
	{

	}

} } 