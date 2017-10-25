#pragma once

namespace sudo { namespace graphics { 

	class Renderable2D;

} } 

namespace sudo { namespace sudo_system {

	class BatchRenderSystem {
	private:
		// Constructor 
		BatchRenderSystem();
		// Destructor 
		~BatchRenderSystem();

	public:
		// Renders the current buffer
		void flush();

		// Inits the neccesary OpenGL stuff
		void init();

		// Submits to the current buffer
		void submit(const graphics::Renderable2D &a_other);
	};

} }