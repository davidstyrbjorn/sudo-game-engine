#pragma once

#include"../graphics/renderable2d_temp.h"

namespace sudo { namespace sudo_system {

#define RENDERER_MAX_SPRITES 10000
#define RENDERER_VERTEX_SIZE sizeof(graphics::VertexData)

#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICIES_SIZE RENDERER_MAX_SPRITES * 6

	class BatchRenderSystem {
	private:
		// Constructor 
		BatchRenderSystem();
		// Destructor 
		~BatchRenderSystem();

		unsigned int m_VBO;
		unsigned int m_VAO;

		unsigned short int m_primitiveCount;

	public:
		// Renders the current buffer
		void flush();

		// Inits the neccesary OpenGL stuff
		void init();

		// Submits to the current buffer
		void submit(const graphics::Renderable2D &a_other);
	};

} }