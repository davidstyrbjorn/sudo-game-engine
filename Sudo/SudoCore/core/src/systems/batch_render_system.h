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
	}
}

namespace sudo { namespace sudo_system { 

// Renderer only takes in triangles for the moment so primitive = 3 vertices
#define MAX_PRIMITIVES 10000
#define VERTEX_SIZE sizeof(graphics::VertexData)
#define PRIMITIVE_SIZE VERTEX_SIZE * 4 // 4 verts in a quad
#define BUFFER_SIZE PRIMITIVE_SIZE * MAX_PRIMITIVES 
#define INDICES_COUNT MAX_PRIMITIVES * 6 // 6 indicies for each quad

#define TRIANGLE_INDICES_COUNT MAX_PRIMITIVES * 3

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
		void Submit(const graphics::Renderable2D *a_primitive, uint a_vertexCount);
		void Flush();

	private:
		/* Batch Renderer data */
		graphics::Shader *m_shader;
		graphics::IndexBuffer *m_quadIndexBuffer;
		graphics::VertexArrayBuffer *m_quadVertexArrayBuffer;


		bool m_isActive;
		unsigned int m_quadBuffer;
		unsigned short int m_quadCount, m_triangleCount;
	};

} } 