#pragma once

#include"sudo_system.h"
#include"../graphics/renderable2d.h"


namespace sudo {
	namespace graphics {
		class Shader;
	}
}

namespace sudo { namespace sudo_system { 

// Renderer only takes in triangles for the moment so primitive = 3 vertices
#define MAX_PRIMITIVES 20000
#define VERTEX_SIZE sizeof(graphics::VertexData)
#define PRIMITIVE_SIZE VERTEX_SIZE * 3
#define BUFFER_SIZE PRIMITIVE_SIZE * MAX_PRIMITIVES

	class BatchRendererSystem : public SudoSystem {
	private:
		/* Private constructor, singleton class */
		BatchRendererSystem();
		static BatchRendererSystem *_instance;

	public:
		/* Method to get pointer to system */
		static BatchRendererSystem *Instance();

		/* Method from SudoSystem base class */
		void Enable() { m_isActive = true; }
		void Disable() { m_isActive = false; }
		void CleanUp() override;
		void Update() override { }
		void Start() override;
			
		// Renderer routines
		void Begin();
		void Submit(graphics::VertexData *a_vertices);
		void Flush();

	private:
		/* Batch Renderer data */
		graphics::Shader *m_shader;
		bool m_isActive;
		unsigned int m_buffer;
		unsigned short int m_primitiveCount; // 16-bit integer (65,536)
	};

} } 