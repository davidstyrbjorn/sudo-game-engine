#pragma once

#include"sudo_system.h"
#include"../graphics/renderable2d.h"
#include"../../definitions.h"
#include<vector>

namespace sudo {
	namespace graphics {
		class Shader;
		class IndexBuffer;
		class VertexArrayBuffer;

		class Texture;
	}
}

namespace sudo { namespace sudo_system { 

#define USE_INDEX_BUFFER 1

	// Renderer pre-processor data
#define MAX_PRIMITIVES 2000
#define VERTEX_SIZE sizeof(graphics::VertexData)

#if USE_INDEX_BUFFER
#define PRIMITIVE_SIZE VERTEX_SIZE * 4 // 6 verts in a quad
#else
#define PRIMITIVE_SIZE VERTEX_SIZE * 6
#endif

#define BUFFER_SIZE PRIMITIVE_SIZE * MAX_PRIMITIVES 
#define INDICES_COUNT MAX_PRIMITIVES * 6

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
		void Submit(graphics::Renderable2D *a_primitive);
		void Flush();
		void End();


	private:
		/* Batch Renderer data */
		GLuint m_vertexArray;
		graphics::Shader *m_shader;
		graphics::VertexData *m_mapBuffer;

		// Texture 
		std::vector<uint> m_textureSlots;

#if USE_INDEX_BUFFER
		graphics::IndexBuffer *m_indexBuffer;
#endif

		bool m_isActive;
		unsigned int m_buffer;
		unsigned short int m_primitiveCount;
	};

} } 